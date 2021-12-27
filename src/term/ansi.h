#pragma once

#include <array>

#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../utils/geometry.h"

namespace term::ansi {
    const auto Csi = utils::slice::from("\x1B[");

    constexpr auto Home = (uint8_t)'H';
    constexpr auto ColumnRelative = (uint8_t)'C';

    const auto NextLine = utils::slice::from("1E");
    const auto Clear = utils::slice::from("2J");
    const auto ClearLine = utils::slice::from("K");

    const auto Dim = utils::slice::from("2m");
    const auto ResetDim = utils::slice::from("22m");
    const auto ResetForeground = utils::slice::from("39m");
    const auto Reset = utils::slice::from("0m");

    constexpr uint8_t ForegroundAttr = 38;
    constexpr uint8_t BackgroundAttr = 48;

    std::array<uint8_t, 9> color_256(const uint8_t attr_code, const uint8_t color_code);
}