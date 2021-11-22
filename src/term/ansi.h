#ifndef ANSI_H
#define ANSI_H

#include <array>

#include "../utils/array.h"
#include "term.h"

namespace {
    constexpr uint8_t Esc = 27;
    constexpr auto Csi = utils::array::array_of<uint8_t>(Esc, (uint8_t)'[');
    constexpr auto Home_ = utils::array::array_of<uint8_t>((uint8_t)'H');
    constexpr auto Clear_ = utils::array::array_of<uint8_t>((uint8_t)'2', (uint8_t)'J');
    constexpr auto NextLine_ = utils::array::array_of<uint8_t>((uint8_t)'1', (uint8_t)'E');
}

namespace term::ansi {
    constexpr auto Reset = utils::array::concat(Csi, Clear_, Csi, Home_);
    constexpr auto NextLine = utils::array::concat(Csi, NextLine_);

    std::array<uint8_t, 10> go_to(const ScreenPosition& col);
}

#endif