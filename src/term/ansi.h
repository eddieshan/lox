#pragma once

#include <array>

#include "../utils/array.h"
#include "../utils/ascii.h"
#include "../utils/geometry.h"

#include "term.h"

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

    constexpr auto Home = escape(utils::array::from<char>('H'));
    constexpr auto NextLine = escape(utils::array::from<char>('1', 'E'));
    constexpr auto Clear = escape(utils::array::from<char>('2', 'J'));
    constexpr auto CursorDn = escape(utils::array::from<char>('B'));
    constexpr auto CursorRt = escape(utils::array::from<char>('C'));
    constexpr auto CursorMv = escape(utils::array::from<char>('\0', '\0', '\0', ';' , '\0', '\0', '\0', 'H'));

    constexpr auto Dim = escape(utils::array::from<char>('2', 'm'));
    constexpr auto ResetDim = escape(utils::array::from<char>('2', '2', 'm'));
    constexpr auto Reset = escape(utils::array::from<char>('0', 'm'));

    constexpr auto ClearScreen = utils::array::concat(Clear, Home);

    constexpr auto Foreground = escape(utils::array::from<char>('3', '8', ';', '5', ';', '\0', '\0', '\0', 'm'));
    constexpr auto Background = escape(utils::array::from<char>('4', '8', ';', '5', ';', '\0', '\0', '\0', 'm'));

    std::array<uint8_t, 11> foreground(const std::array<char, 3>& color_code);
    std::array<uint8_t, 11> background(const std::array<char, 3>& color_code);
}