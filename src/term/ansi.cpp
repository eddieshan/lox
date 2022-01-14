#include <array>

#include "ansi.h"

using namespace utils;
using namespace term;

constexpr uint8_t ForegroundAttr = 38;
constexpr uint8_t BackgroundAttr = 48;

ansi::ColorAttribute ansi::foreground(const uint8_t color) {
    return ColorAttribute { attr: ForegroundAttr, color: color };
}

ansi::ColorAttribute ansi::background(const uint8_t color) {
    return ColorAttribute { attr: BackgroundAttr, color: color };
}