#include <cstring>

#include "../utils/slice.h"
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

std::pair<bool, size_t> capture(const Slice<uint8_t>& text, const Slice<uint8_t>& start, const Slice<uint8_t>& end) {
    if((text.size >= start.size + end.size) && (std::memcmp(start.data, text.data, start.size) == 0)) {
        const auto limit = text.size - end.size;
        for(auto index = start.size; index <= limit; ++index) {
            if(std::memcmp(end.data, text.data + index, end.size) == 0) {
                const auto last = index + end.size - 1;

                // If the terminating delimiter is a line break, exclude it from the token span.
                // Otherwise line breaks will not be rendered properly. 
                // A horrible fix but there but there is no other way to deal with the issue.
                // Line break handling is known for messing up lexing & parsing.
                const auto match_size = text.data[last] == ascii::Lf? last : index + end.size;
                return std::make_pair(true, match_size);
            }
        }
    }

    return std::make_pair(false, 0);
}

std::tuple<bool, size_t, TokenType> delimited_token_type(const Slice<uint8_t>& text, const Grammar& grammar) {

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
                return std::make_tuple(true, match_size, grammar.delimited_tokens.data[i].type);
            }
        }
    }

    return std::make_tuple(false, 0, TokenType::Plain);
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
        if(_text.data[i] == val || _text.data[i] == utils::ascii::Lf) {
            return i;
        }
    }

    return _text.size;
}

Token Tokenizer::next() {

    const auto symbol = _text.data[_pos];

    if(symbol == ascii::Lf) {
        ++_pos;

        return Token {
            type: TokenType::NewLine,
            span: Slice(_text.data, 0)
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
        const auto tail = Slice(_text.data + _pos, _text.size - _pos);
        const auto [is_capture, match_size, type] = delimited_token_type(tail, _grammar);

        if(is_capture) {
            const auto span = Slice(_text.data + _pos, match_size);
            _pos += match_size;

            return Token {
                type: type,
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
}