#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "navigation.h"

using namespace utils;
using namespace text;

Position navigation::screen_position(const utils::Slice<uint8_t>& text, const size_t pos) {
    auto screen_pos = Position { 0, 0 };
    size_t last_cr = 0;

    for(auto i = 0; i < pos; ++i) {
        if(text.data[i] == ascii::CarriageReturn) {
            ++screen_pos.row;
            screen_pos.col = 0;
        } else {
            ++screen_pos.col;
        }
    }

    return screen_pos;
}

size_t navigation::col_forward(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos < text.size - 1? pos + 1 : pos;
}

size_t navigation::col_back(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos > 0? pos - 1 : pos;
}

size_t navigation::row_forward(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step) {
    size_t last_cr = 0, current_col = 0;

    for(auto i = 1; i <= pos && text.data[pos - i] != ascii::CarriageReturn; ++i, ++current_col) {
    }

    size_t new_cursor = pos, row = 0, next_col = 0;

    while(new_cursor < text.size && row <= step && next_col <= current_col) {
        if(text.data[new_cursor] == ascii::CarriageReturn) {
            ++row;
        }
        next_col += (row/step);
        new_cursor++;
    }

    return new_cursor < text.size? new_cursor : text.size - 1;
}

size_t navigation::row_back(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step) {

    size_t row = 0, current_col = 0, last_prev_col = 0, new_cursor = pos, distance = 1;

    while(distance <= pos && row <= step) {
        new_cursor = pos - distance;

        if(text.data[new_cursor] == ascii::CarriageReturn) {
            ++row;
        } else if(row == step) {
            ++last_prev_col;
        } else if(row == 0) {
            ++current_col;
        } 

        ++distance;
    }

    const auto new_col = current_col > last_prev_col? last_prev_col : current_col;
    return new_cursor == 0? new_col : new_cursor + new_col + 1;
}