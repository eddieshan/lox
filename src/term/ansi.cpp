#include <array>

#include "../utils/array.h"
#include "ansi.h"

using namespace utils;

std::array<uint8_t, 11> term::ansi::foreground(const std::array<char, 3>& color_code) {
    auto seq = ansi::Foreground;
    std::copy(color_code.data(), color_code.data() + color_code.size(), seq.data() + 7);
    return seq;
}

std::array<uint8_t, 11> term::ansi::background(const std::array<char, 3>& color_code) {
    auto seq = ansi::Background;
    std::copy(color_code.data(), color_code.data() + color_code.size(), seq.data() + 7);
    return seq;
}