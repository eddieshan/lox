#include <array>

#include "../utils/array.h"
#include "../utils/convert.h"
#include "ansi.h"

using namespace utils;

std::array<uint8_t, 11> term::ansi::color_256(const uint8_t attr_code, const uint8_t color_code) {
    char seq[] = "\0\0;5;\0\0\0m";
    convert::to_chars_2(attr_code, (uint8_t*)seq);
    convert::to_chars_3(color_code, (uint8_t*)seq + 5);
    return escape(seq);
}