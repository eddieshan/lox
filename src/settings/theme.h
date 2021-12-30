#pragma once

#include "../utils/slice.h"
#include "../term/ansi.h"
#include "../syntax/tokenize.h"

namespace settings::theme {
    const auto Foreground = term::ansi::color_256(term::ansi::ForegroundAttr, 254);
    const auto Background = term::ansi::color_256(term::ansi::BackgroundAttr, 235);

    const auto Plain = term::ansi::color_256(term::ansi::ForegroundAttr, 81);
    const auto Operator = term::ansi::color_256(term::ansi::ForegroundAttr, 255);
    const auto Delimiter = term::ansi::color_256(term::ansi::ForegroundAttr, 255);    
    const auto Keyword = term::ansi::color_256(term::ansi::ForegroundAttr, 177);
    const auto TypeKeyword = term::ansi::color_256(term::ansi::ForegroundAttr, 75);
    const auto Number = term::ansi::color_256(term::ansi::ForegroundAttr, 10);
    const auto String = term::ansi::color_256(term::ansi::ForegroundAttr, 214);
    const auto Comment = term::ansi::color_256(term::ansi::ForegroundAttr, 28);

    namespace command_line {
        const auto Foreground = term::ansi::color_256(term::ansi::ForegroundAttr, 255);
        const auto Background = term::ansi::color_256(term::ansi::BackgroundAttr, 33);
    }

    const std::array<uint8_t, 9> syntax_style(syntax::TokenType token_type);
}