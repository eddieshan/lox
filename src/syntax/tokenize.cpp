#include <cstring>

#include "../utils/slice.h"
#include "../utils/range.h"
#include "../utils/ascii.h"
#include "grammar.h"
#include "tokenize.h"

using namespace utils;
using namespace syntax;

bool is_number(const Slice<uint8_t>& text) {
    for(auto i = 0; i < text.size; ++i) {
        if(!range::contains(ascii::Numbers, text.data[i])) {
            return false;
        }
    }

    return true;
}

TokenType fixed_token(const Slice<uint8_t>& text, const Grammar& grammar) {

    if(is_number(text)) {
        return TokenType::NumericLiteral;
    }

    for(auto i = 0; i < grammar.fixed_tokens.size; ++i) {
        const auto tokens = grammar.fixed_tokens.data[i].tokens.get();

        size_t length_index = 0;

        while(length_index < grammar.fixed_tokens.data[i].size) {
            const auto token_size = tokens[length_index];
            const auto token_start = tokens + length_index + 1;

            if(token_size == text.size && std::memcmp(token_start, text.data, token_size) == 0) {
                return grammar.fixed_tokens.data[i].type;
            }

            length_index += (token_size + 1);
        }
    }

    return TokenType::Plain;
}

std::pair<bool, size_t> capture(const Slice<uint8_t>& text, const Slice<uint8_t>& start, const Slice<uint8_t>& end) {
    if((text.size >= start.size + end.size) && (std::memcmp(start.data, text.data, start.size) == 0)) {
        const auto limit = text.size - end.size;
        for(auto index = start.size; index <= limit; ++index) {
            if(std::memcmp(end.data, text.data + index, end.size) == 0) {
                const auto match_size = index + end.size;
                return std::make_pair(true, match_size);
            }
        }

        return std::make_pair(true, text.size);
    }

    return std::make_pair(false, 0);
}

std::tuple<size_t, TokenType> delimited_token(const Slice<uint8_t>& text, const Grammar& grammar) {

    for(auto i = 0; i < grammar.delimited_tokens.size; ++i) {
        const auto tokens = grammar.delimited_tokens.data[i].tokens.get();

        size_t length_index = 0;

        while(length_index < grammar.delimited_tokens.data[i].size) {
            const auto start = Slice(tokens + length_index + 1, tokens[length_index]);
            length_index += (tokens[length_index] + 1);
            const auto end = Slice(tokens + length_index + 1, tokens[length_index]);
            length_index += (tokens[length_index] + 1);

            const auto [is_capture, match_size] = capture(text, start, end);

            if(is_capture) {
                return std::make_tuple(match_size, grammar.delimited_tokens.data[i].type);
            }
        }
    }

    return std::make_tuple(0, TokenType::Plain);
}

bool is_delimiter(const uint8_t val, const Grammar& grammar) {
    return slice::contains(grammar.delimiters, val);
}

TokenizationState tokenizer::next(const Slice<uint8_t>& tail, const Grammar& grammar) {

    auto type = TokenType::Plain;
    size_t next_pos = 0;

    if(const auto pos = match<is_delimiter>(tail, grammar); pos > 0) {
        next_pos = pos;
        type = TokenType::Delimiter;
    } else if(const auto [pos, token_type] = delimited_token(tail, grammar); pos > 0) {
        next_pos = pos;
        type = token_type;
    } else {
        next_pos = find<is_delimiter>(tail, grammar);
        const auto span = Slice(tail.data, next_pos);
        type = fixed_token(span, grammar);
    }

    return TokenizationState {
        tail: Slice(tail.data + next_pos, tail.size - next_pos),
        span: Slice(tail.data, next_pos),
        type: type         
    };
}