#include <cstddef>

#include "../utils/array.h"
#include "../term/ansi.h"

namespace {
    constexpr auto ForegroundCode = utils::array::from<char>('2', '5', '4');
    constexpr auto BackgroundCode = utils::array::from<char>('2', '3', '5');
}

namespace settings::theme {
    const auto Foreground = term::ansi::foreground(ForegroundCode);
    const auto Background = term::ansi::background(BackgroundCode);

    constexpr auto Plain = term::ansi::escape("38;5;87m");
    constexpr auto Keyword = term::ansi::escape("38;5;174m");
    constexpr auto TypeKeyword = term::ansi::escape("38;5;75m");
}