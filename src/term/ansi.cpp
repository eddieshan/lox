#include <array>

#include "../utils/convert.h"
#include "ansi.h"

using namespace utils;

std::array<uint8_t, 9> term::ansi::color_256(const uint8_t attr_code, const uint8_t color_code) {
    std::array<uint8_t, 9> seq { '\0', '\0', ';', '5', ';', '\0', '\0', '\0', 'm' };
    convert::to_chars_2(attr_code, (uint8_t*)seq.data());
    convert::to_chars_3(color_code, (uint8_t*)seq.data() + 5);
    return seq;
}