#include "../utils/array.h"
#include "../term/ansi.h"

namespace settings::theme {
    const auto Foreground = term::ansi::color_256(term::ansi::ForegroundAttr, 254);
    const auto Background = term::ansi::color_256(term::ansi::BackgroundAttr, 235);

    const auto Plain = term::ansi::color_256(term::ansi::ForegroundAttr, 87);
    const auto Keyword = term::ansi::color_256(term::ansi::ForegroundAttr, 174);
    const auto TypeKeyword = term::ansi::color_256(term::ansi::ForegroundAttr, 75);
}