#pragma once

#include <array>

#include "../utils/array.h"
#include "../utils/ascii.h"
#include "../utils/geometry.h"

namespace term::ansi {
    constexpr auto Csi = utils::array::from<uint8_t>(utils::ascii::Esc, (uint8_t)'[');

    template<size_t Size>
    constexpr std::array<uint8_t, Size + Csi.size()> escape(const std::array<char, Size> chars) {
        constexpr auto csi_size = Csi.size();
        constexpr auto total_size = Size + csi_size;
        std::array<uint8_t, total_size> result { 0 };

        for(auto i = 0; i < Csi.size(); ++i) {
            result[i] = Csi[i];
        }

        for(size_t i = csi_size, j = 0; i < total_size; ++i, ++j) {
            result[i] = (uint8_t)chars[j];
        }

        return result;
    }

    // Creates an escape sequence prefixed with CSI.
    // chars is expected to be a zero terminated char array.
    // The terminating zero is not copied so the size of the
    // result is Size - 1.
    template<size_t Size>
    constexpr std::array<uint8_t, Size + Csi.size() - 1> escape(const char (&chars)[Size]) {
        constexpr auto csi_size = Csi.size();
        constexpr auto total_size = Size + csi_size - 1;
        std::array<uint8_t, total_size> result { 0 };

        for(auto i = 0; i < csi_size; ++i) {
            result[i] = Csi[i];
        }

        for(size_t i = csi_size, j = 0; i < total_size; ++i, ++j) {
            result[i] = (uint8_t)chars[j];
        }

        return result;
    }    

    constexpr auto Home = escape("H");
    constexpr auto NextLine = escape("1E");
    constexpr auto Clear = escape("2J");
    constexpr auto ClearLine = escape("K");
    constexpr auto CursorDn = escape("B");
    constexpr auto CursorRt = escape("C");
    constexpr auto CursorMv = escape("\0\0\0;\0\0\0H");

    constexpr auto Dim = escape("2m");
    constexpr auto ResetDim = escape("22m");
    constexpr auto ResetForeground = escape("39m");
    constexpr auto Reset = escape("0m");

    constexpr auto ClearScreen = utils::array::concat(Clear, Home);

    constexpr uint8_t ForegroundAttr = 38;
    constexpr uint8_t BackgroundAttr = 48;

    std::array<uint8_t, 11> color_256(const uint8_t attr_code, const uint8_t color_code);
}