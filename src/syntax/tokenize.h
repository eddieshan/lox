#pragma once

#include <memory>

#include "../utils/slice.h"
#include "../utils/ascii.h"

namespace syntax {

    typedef bool (*predicate)(const uint8_t val);

    enum class TokenType {
        Plain,
        Keyword,
        TypeKeyword,
        NumericLiteral,
        StringLiteral,
        Identifier,
        NewLine
    };

    struct Token {
        TokenType type;
        utils::Slice<uint8_t> span;
    };

    TokenType token_type(const utils::Slice<uint8_t>& sequence);

    class Tokenizer {
        private:
            utils::Slice<uint8_t>& _text;
            size_t _pos;

        public:
            Tokenizer(utils::Slice<uint8_t>& text);
            bool is_end() const;
            Token next();

            template<predicate pred>
            size_t find_next() {
                for(auto i = _pos; i < _text.size; ++i) {
                    if(pred(_text.data[i]) || _text.data[i] == utils::ascii::CarriageReturn) {
                        return i;
                    }
                }

                return _text.size;
            }
    };
}
