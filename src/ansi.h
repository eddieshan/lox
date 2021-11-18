#ifndef ANSI_H
#define ANSI_H

#include <array>

#include "utils.h"
#include "term.h"

namespace term::ansi {

    constexpr std::array<uint8_t, 3> Seq { "\x1b[" };

    constexpr auto Home  = utils::array_of<uint8_t>(27, 91, 72); // \x1b[H
    constexpr auto Clear = utils::array_of<uint8_t>(27, 91, 50, 74); // \x1b[2J

    constexpr std::array<uint8_t, 5> Reset { "\x1b[0m" };
    constexpr std::array<uint8_t, 5> NextLine = { "\x1b[1E" };
    constexpr std::array<uint8_t, 6> Del1 { "\x1b[1P" };
    constexpr std::array<uint8_t, 9> BackDel1 { "\x1b[1D\x1b[1P" };
    constexpr std::array<uint8_t, 5> Underline { "\x1b[4m" };
    constexpr std::array<uint8_t, 5> StrikeThrough { "\x1b[9m" };

    std::array<uint8_t, 10> go_to(const ScreenPosition& col);
}

#endif