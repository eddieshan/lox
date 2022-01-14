#pragma once

#include "../utils/slice.h"
#include "../term/ansi.h"
#include "../syntax/tokenize.h"

namespace settings::theme {
    const auto Foreground = term::ansi::foreground(254);
    const auto Background = term::ansi::background(235);
    
    namespace syntax_highlight {
        const auto Plain = term::ansi::foreground(81);
        const auto Operator = term::ansi::foreground(255);
        const auto Delimiter = term::ansi::foreground(255);
        const auto Keyword = term::ansi::foreground(177);
        const auto TypeKeyword = term::ansi::foreground(75);
        const auto Number = term::ansi::foreground(10);
        const auto String = term::ansi::foreground(214);
        const auto Comment = term::ansi::foreground(28);
        const auto Function = term::ansi::foreground(227);
    }

    namespace command_line {
        const auto Foreground = term::ansi::foreground(255);
        const auto Background = term::ansi::background(33);
    }

    const term::ansi::ColorAttribute syntax_style(syntax::TokenType token_type);

}