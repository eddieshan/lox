#pragma once

#include <array>
#include <cstdint>

#include "../utils/slice.h"
#include "../utils/geometry.h"

namespace term::ansi {
    const auto Csi = utils::slice::from("\x1B[");

    constexpr auto Home = (uint8_t)'H';
    constexpr auto ColumnRelative = (uint8_t)'C';

    const auto NextLine = utils::slice::from("1E");
    const auto Clear = utils::slice::from("2J");
    const auto ClearLine = (uint8_t)'K';

    const auto Dim = utils::slice::from("2m");
    const auto ResetDim = utils::slice::from("22m");
    const auto ResetForeground = utils::slice::from("39m");
    const auto Reset = utils::slice::from("0m");

    struct ColorAttribute {
        uint8_t attr;
        uint8_t color;
    };

    ColorAttribute foreground(const uint8_t color);
    ColorAttribute background(const uint8_t color);
}