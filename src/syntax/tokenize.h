#pragma once

#include <memory>

#include "../utils/slice.h"
#include "../utils/ascii.h"

namespace syntax {

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

    struct TokenGroup {
        std::unique_ptr<uint8_t[]> tokens;
        size_t size;
        TokenType type;
    };

    struct Grammar {
        utils::Slice<TokenGroup> tokens;
        uint8_t delimiter;
    };

    typedef bool (*predicate)(const uint8_t val, const Grammar& grammar);

    TokenGroup tokens(const char* tokens_def, const TokenType token_type);

    class Tokenizer {
        private:
            const utils::Slice<uint8_t>& _text;
            const Grammar& _grammar;
            size_t _pos;

            template<predicate pred>
            size_t find_next() {
                for(auto i = _pos; i < _text.size; ++i) {
                    if(pred(_text.data[i], _grammar) || _text.data[i] == utils::ascii::CarriageReturn) {
                        return i;
                    }
                }

                return _text.size;
            }

        public:
            Tokenizer(const utils::Slice<uint8_t>& text, const Grammar& grammar);
            bool is_end() const;
            Token next();

    };
}