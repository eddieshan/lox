#pragma once

#include "../utils/slice.h"
#include "grammar.h"

namespace syntax {
    struct TokenizationState {
        utils::Slice<uint8_t> tail;
        utils::Slice<uint8_t> span;
        TokenType type;
    };

    namespace tokenizer {
        TokenizationState next(const utils::Slice<uint8_t>& tail, const Grammar& grammar);
    }
}