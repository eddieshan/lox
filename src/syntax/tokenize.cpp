#include <cstring>

#include "../utils/slice.h"
#include "../utils/packed_array.h"
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
    return slice::any(grammar.delimiters, val);
}

bool is_digit(const uint8_t val) {
    constexpr auto decimal_delimiter = (uint8_t)'.';
    return range::any(ascii::Numbers, val) || val == decimal_delimiter;
}

bool is_operator(const uint8_t val, const Grammar& grammar) {
    return slice::any(grammar.operators, val);
}

bool is_identifier(const uint8_t val) {
    constexpr auto id_delimiter = (uint8_t)'_';

    return range::any(ascii::LettersLower, val) ||
           range::any(ascii::LettersUpper, val) ||
           val == id_delimiter;
}

size_t match_fixed(const Slice<uint8_t>& text, const PackedArray& token_group) {

    auto iterator = PackedArray::PackedArrayIterator(token_group);
    auto token = iterator.next();

    while(token.size > 0) {
        if(token.size <= text.size && 
           std::memcmp(token.data, text.data, token.size) == 0 && 
           !is_identifier(text.data[token.size])) {
            return token.size;
        }

        token = iterator.next();
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

size_t match_delimited(const Slice<uint8_t>& text, const PackedArray& token_group) {

    auto iterator = PackedArray::PackedArrayIterator(token_group);
    auto delimiter_start = iterator.next();

    while(delimiter_start.size > 0) {
        auto delimiter_end = iterator.next();
        const auto size = match(text, delimiter_start, delimiter_end);

        if(size > 0) {
            return size;
        }

        delimiter_start = iterator.next();
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
    } else if(const auto pos = slice::match<uint8_t, is_identifier>(tail); pos > 0) {
        const auto next_delimiter_pos = slice::match(tail, ascii::WhiteSpace, pos);
        const auto type = 
            next_delimiter_pos == tail.size || 
            tail.data[pos] != grammar.function_call_delimiters.start? TokenType::Plain : TokenType::Function;
        return next_state(tail, pos, type);
    } else {
        return next_state(tail, tail.size, TokenType::Plain);
    }
}