#pragma once

#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "grammar.h"

namespace syntax {

    typedef bool (*predicate)(const uint8_t val, const Grammar& grammar);

    TokenGroup tokens(const char* tokens_def, const TokenType token_type);

    class Tokenizer {
        private:
            const utils::Slice<uint8_t>& _text;
            const Grammar& _grammar;
            size_t _pos;

            template<predicate pred>
            size_t find_next() {
                for(auto i = _pos + 1; i < _text.size; ++i) {
                    if(pred(_text.data[i], _grammar) || _text.data[i] == utils::ascii::CarriageReturn) {
                        return i;
                    }
                }

                return _text.size;
            }

            size_t find_next(const uint8_t);

        public:
            Tokenizer(const utils::Slice<uint8_t>& text, const Grammar& grammar);
            bool is_end() const;
            Token next();

    };
}