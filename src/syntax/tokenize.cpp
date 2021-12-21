#include <cstring>

#include "../utils/slice.h"
#include "../utils/array.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "grammar.h"
#include "tokenize.h"

using namespace utils;
using namespace syntax;

bool is_number(const Slice<uint8_t>& sequence) {
    for(auto i = 0; i < sequence.size; ++i) {
        if(sequence.data[i] < ascii::Zero || sequence.data[i] > ascii::Nine) {
            return false;
        }
    }

    return true;
}

TokenType token_type(const Slice<uint8_t>& sequence, const Grammar& grammar) {

    if(is_number(sequence)) {
        return TokenType::NumericLiteral;
    }

    for(auto i = 0; i < grammar.tokens.size; ++i) {
        const auto tokens = grammar.tokens.data[i].tokens.get();

        size_t length_index = 0;

        while(length_index < grammar.tokens.data[i].size) {
            const auto token_size = tokens[length_index];
            const auto token_start = tokens + length_index + 1;

            if(token_size == sequence.size && std::memcmp(token_start, sequence.data, token_size) == 0) {
                return grammar.tokens.data[i].type;
            }

            length_index += (token_size + 1);
        }
    }

    return TokenType::Plain;
}

bool is_delimiter(const uint8_t val, const Grammar& grammar) {
    return slice::contains(grammar.delimiters, val);
}

bool is_not_delimiter(const uint8_t val, const Grammar& grammar) {
    return !slice::contains(grammar.delimiters, val);
}

Tokenizer::Tokenizer(const Slice<uint8_t>& text, const Grammar& grammar): 
    _text(text),
    _grammar(grammar),
    _pos(0) {}

bool Tokenizer::is_end() const {
    return _text.size == 0 || _pos == _text.size;
}

size_t Tokenizer::find_next(const uint8_t val) {
    for(auto i = _pos + 1; i < _text.size; ++i) {
        if(_text.data[i] == val || _text.data[i] == utils::ascii::CarriageReturn) {
            return i;
        }
    }

    return _text.size;
}

Token Tokenizer::next() {

    const auto symbol = _text.data[_pos];

    if(symbol == ascii::CarriageReturn) {
        ++_pos;

        return Token {
            type: TokenType::NewLine,
            span: Slice(_text.data, 0)
        };
    } else if(symbol == ascii::Quote) {
        const auto next_pos = find_next(ascii::Quote);
        const auto span = Slice(_text.data + _pos, next_pos - _pos + 1);
        _pos = next_pos == _text.size? _text.size : next_pos + 1;

        return Token {
            type: next_pos == _text.size? TokenType::Plain : TokenType::StringLiteral,
            span: span
        };
    } else if(slice::contains(_grammar.delimiters, symbol)) {
        const auto next_pos = find_next<is_not_delimiter>();
        const auto span = Slice(_text.data + _pos, next_pos - _pos);
        _pos = next_pos;

        return Token {
            type: token_type(span, _grammar),
            span: span
        };
    } else {
        const auto next_pos = find_next<is_delimiter>();
        const auto span = Slice(_text.data + _pos, next_pos - _pos);
        _pos = next_pos;

        return Token {
            type: token_type(span, _grammar),
            span: span
        };
    }
}