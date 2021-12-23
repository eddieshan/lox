#pragma once

#include <cstdint>

namespace utils {
    struct Position {
        uint32_t row;
        uint32_t col;
    };

    utils::Position operator+(const utils::Position& a, const utils::Position& b);

    struct WindowSize {
        uint32_t rows;
        uint32_t cols;
    };
}