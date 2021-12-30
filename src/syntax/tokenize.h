#pragma once

#include "../utils/slice.h"
#include "grammar.h"

namespace syntax {

    using predicate = bool (*)(const uint8_t val, const Grammar& grammar);

    struct TokenizationState {
        utils::Slice<uint8_t> tail;
        TokenType type;
        utils::Slice<uint8_t> span;        
    };

    namespace tokenizer {
        template<predicate pred>
        size_t find_next(const utils::Slice<uint8_t>& text, const Grammar& grammar) {
            for(auto i = 1; i < text.size; ++i) {
                if(pred(text.data[i], grammar)) {
                    return i;
                }
            }

            return text.size;
        }

        template<predicate pred>
        size_t match(const utils::Slice<uint8_t>& text, const Grammar& grammar) {
            auto i = 0;
            while(i < text.size && pred(text.data[i], grammar)) {
                ++i;
            }

            return i;
        }

        TokenizationState next(const utils::Slice<uint8_t>& tail, const Grammar& grammar);
    }
}