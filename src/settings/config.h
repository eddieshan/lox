#pragma once

#include "../utils/slice.h"
#include "../syntax/grammar.h"

namespace settings {
    struct Config {
        syntax::Grammar grammar;

        Config(syntax::Grammar grammar_):
            grammar(std::move(grammar_)) {}

        Config(Config&& config) noexcept:
            grammar(std::move(config.grammar)) {}
    };
}