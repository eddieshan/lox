#pragma once

namespace utils {
    struct Position {
        unsigned int row;
        unsigned int col;
    };

    utils::Position operator+(const utils::Position& a, const utils::Position& b);

    struct WindowSize {
        unsigned int rows;
        unsigned int cols;
    };
}