#include "geometry.h"

utils::Position utils::operator+(const utils::Position& a, const utils::Position& b) {
    return utils::Position { row: a.row + b.row, col: a.col + b.col };
}