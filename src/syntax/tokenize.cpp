#include <memory>
#include <cstring>

#include "../utils/slice.h"
#include "../utils/array.h"
#include "../utils/ascii.h"
#include "tokenize.h"

using namespace utils;
using namespace syntax;

constexpr auto TokenDelimiter = '|';

TokenGroup syntax::tokens(const char* tokens_def, const TokenType token_type) {

    const auto tokens_length = strlen(tokens_def) + 1;

    auto token_group = TokenGroup {
        tokens: std::make_unique<uint8_t[]>(tokens_length),
        size: tokens_length,
        type: token_type
    };

    const auto tokens = token_group.tokens.get();
    auto index = 0;

    for(auto i = 0; i < tokens_length; ++i) {
        if(tokens_def[i] == TokenDelimiter || tokens_def[i] == '\0') {
            const auto offset = index == 0? index : index + 1;
            const auto token_size = i - offset;

            tokens[offset] = token_size;
            std::copy(tokens_def + offset, tokens_def + i, tokens + offset + 1);

            index = i;
        }
    }

    return token_group;
}

TokenType token_type(const Slice<uint8_t>& sequence, const Grammar& grammar) {

    for(auto i = 0; i < grammar.tokens.size; ++i) {
        const auto tokens = grammar.tokens.data[i].tokens.get();

        size_t length_index = 0;

        while(length_index < grammar.tokens.data[i].size) {
            const auto token_size = tokens[length_index];
            const auto token_index = length_index + 1;

            if(token_size == sequence.size) {
                if(std::memcmp(tokens + token_index, sequence.data, token_size) == 0) {
                    return grammar.tokens.data[i].type;
                }
            }

            length_index += (token_size + 1);
        }
    }

    return TokenType::Plain;
}

bool is_delimiter(const uint8_t val, const Grammar& grammar) {
    return val == grammar.delimiter;
}

bool is_not_delimiter(const uint8_t val, const Grammar& grammar) {
    return val != grammar.delimiter;
}

Tokenizer::Tokenizer(const Slice<uint8_t>& text, const Grammar& grammar): 
    _text(text),
    _grammar(grammar),
    _pos(0) {}

bool Tokenizer::is_end() const {
    return _text.size == 0 || _pos == _text.size;
}

Token Tokenizer::next() {

    const auto is_new_line = _text.data[_pos] == ascii::CarriageReturn;

    if(is_new_line) {
        if(_pos < _text.size) {
            ++_pos;
        }
        return Token {
            type: TokenType::NewLine,
            span: Slice(_text.data, 0)
        };
    } else {
        const auto marker = is_delimiter(_text.data[_pos], _grammar)? find_next<is_not_delimiter>() : find_next<is_delimiter>();
        const auto span = Slice(_text.data + _pos, marker - _pos);
        _pos = marker;

        return Token {
            type: token_type(span, _grammar),
            span: span
        };
    }
}