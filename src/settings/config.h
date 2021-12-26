#pragma once

#include "../utils/slice.h"
#include "../syntax/grammar.h"

namespace settings {
    struct Config {
        syntax::Grammar grammar;
        utils::Slice<uint8_t> preamble;
    };
}