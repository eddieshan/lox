#ifndef ANSI_H
#define ANSI_H

#include <array>

#include "../utils/array.h"
#include "../utils/geometry.h"

#include "term.h"

namespace {
    constexpr uint8_t Esc = 27;
    constexpr auto Home_ = utils::array::from<uint8_t>((uint8_t)'H');
    constexpr auto Clear_ = utils::array::from<uint8_t>((uint8_t)'2', (uint8_t)'J');
    constexpr auto NextLine_ = utils::array::from<uint8_t>((uint8_t)'1', (uint8_t)'E');
    constexpr auto CursorDn_ = utils::array::from<uint8_t>((uint8_t)'B');
    constexpr auto CursorRt_ = utils::array::from<uint8_t>((uint8_t)'C');
    constexpr auto Dim_ = utils::array::from<uint8_t>((uint8_t)'2', (uint8_t)'m');
    constexpr auto Reset_ = utils::array::from<uint8_t>((uint8_t)'0', (uint8_t)'m');
}

namespace term::ansi {
    constexpr auto Csi = utils::array::from<uint8_t>(Esc, (uint8_t)'[');
    constexpr auto Home = utils::array::concat(Csi, Home_);
    constexpr auto NextLine = utils::array::concat(Csi, NextLine_);

    constexpr auto CursorDn = utils::array::concat(Csi, CursorDn_);

    constexpr auto ClearScreen = utils::array::concat(Csi, Clear_, Csi, Home_);
    
    constexpr auto Reset = utils::array::concat(Csi, Reset_);
    constexpr auto Dim = utils::array::concat(Csi, Dim_);

    std::array<uint8_t, 10> go_to(const utils::Position& col);
}

#endif