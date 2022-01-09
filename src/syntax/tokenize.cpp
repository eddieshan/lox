#include <cstring>

#include "../utils/slice.h"
#include "../utils/range.h"
#include "../utils/ascii.h"
#include "grammar.h"
#include "tokenize.h"

using namespace utils;
using namespace syntax;

using GrammarPredicate = bool (*)(const uint8_t val, const Grammar& grammar);

template<GrammarPredicate pred>
size_t match(const utils::Slice<uint8_t>& text, const Grammar& grammar) {
    auto i = 0;
    while(i < text.size && pred(text.data[i], grammar)) {
        ++i;
    }

    return i;
}

bool is_delimiter(const uint8_t val, const Grammar& grammar) {
    return slice::contains(grammar.delimiters, val);
}

bool is_digit(const uint8_t val) {
    constexpr auto decimal_delimiter = (uint8_t)'.';
    return range::contains(ascii::Numbers, val) || val == decimal_delimiter;
}

bool is_operator(const uint8_t val, const Grammar& grammar) {
    return slice::contains(grammar.operators, val);
}

bool is_alphanumeric(const uint8_t val) {
    constexpr auto id_delimiter = (uint8_t)'_';
    return range::contains(ascii::LettersLower, val) ||
           range::contains(ascii::LettersUpper, val) ||
           val == id_delimiter;
}

size_t match_fixed(const Slice<uint8_t>& text, const TokenGroup& token_group) {
    const auto tokens = token_group.tokens.get();

    size_t length_index = 0;

    while(length_index < token_group.size) {
        const auto token_size = tokens[length_index];
        const auto token_start = tokens + length_index + 1;

        if(token_size <= text.size && 
           std::memcmp(token_start, text.data, token_size) == 0 && 
           !is_alphanumeric(text.data[token_size])) {
            return token_size;
        }

        length_index += (token_size + 1);
    }

    return 0;
}

size_t match(const Slice<uint8_t>& text, const Slice<uint8_t>& start, const Slice<uint8_t>& end) {
    if((text.size >= start.size + end.size) && (std::memcmp(start.data, text.data, start.size) == 0)) {
        if(end.size > 0) {
            const auto limit = text.size - end.size;
            for(auto index = start.size; index <= limit; ++index) {
                if(std::memcmp(end.data, text.data + index, end.size) == 0) {
                    return index + end.size;
                }
            }
        }

        return text.size;
    }

    return 0;
}

size_t match_delimited(const Slice<uint8_t>& text, const TokenGroup& token_group) {

    const auto tokens = token_group.tokens.get();
    size_t length_index = 0;

    while(length_index < token_group.size) {
        const auto start = Slice(tokens + length_index + 1, tokens[length_index]);
        length_index += (tokens[length_index] + 1);
        const auto end = Slice(tokens + length_index + 1, tokens[length_index]);
        length_index += (tokens[length_index] + 1);

        const auto size = match(text, start, end);

        if(size > 0) {
            return size;
        }
    }

    return 0;
}

TokenizationState next_state(const Slice<uint8_t>& tail, const size_t pos, const TokenType token_type) {
    return TokenizationState {
        tail: Slice(tail.data + pos, tail.size - pos),
        span: Slice(tail.data, pos),
        type: token_type
    };
}

TokenizationState tokenizer::next(const Slice<uint8_t>& tail, const Grammar& grammar) {
    if(const auto pos = match<is_delimiter>(tail, grammar); pos > 0) {
        return next_state(tail, pos, TokenType::Delimiter);
    } else if(const auto pos = match_delimited(tail, grammar.string_delimiters); pos > 0) {
        return next_state(tail, pos, TokenType::StringLiteral);
    } else if(const auto pos = match_delimited(tail, grammar.comment_delimiters); pos > 0) {
        return next_state(tail, pos, TokenType::Comment);
    } else if(const auto pos = slice::match<uint8_t, is_digit>(tail); pos > 0) {
        return next_state(tail, pos, TokenType::NumericLiteral);
    } else if(const auto pos = match<is_operator>(tail, grammar); pos > 0) {
        return next_state(tail, pos, TokenType::Operator);
    } else if(const auto pos = match_fixed(tail, grammar.keyword_delimiters); pos > 0) {
        return next_state(tail, pos, TokenType::Keyword);
    } else if(const auto pos = match_fixed(tail, grammar.type_delimiters); pos > 0) {
        return next_state(tail, pos, TokenType::TypeKeyword);
    } else if(const auto pos = slice::match<uint8_t, is_alphanumeric>(tail); pos > 0) {
        return next_state(tail, pos, TokenType::Plain);
    } else {
        return next_state(tail, tail.size, TokenType::Plain);        
    }
}