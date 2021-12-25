#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../models/common.h"

#include "navigation.h"

using namespace utils;
using namespace models;
using namespace text;

TextCursor navigation::text_cursor(const utils::Slice<uint8_t>& text, const size_t pos) {
    auto cursor = TextCursor {
        pos: Position { 0, 0 },
        n_lines: 1
    };

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;

        if(i < pos) {
            if(is_line_break) {
                ++cursor.pos.row;
                cursor.pos.col = 0;
            } else {
                ++cursor.pos.col;
            }
        }
        
        if(is_line_break) {
            ++cursor.n_lines;
        }
    }

    return cursor;
}

size_t navigation::col_forward(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos < text.size? pos + 1 : pos;
}

size_t navigation::col_back(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos > 0? pos - 1 : pos;
}

size_t navigation::row_forward(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step) {
    size_t last_cr = 0, current_col = 0;

    for(auto i = 1; i <= pos && text.data[pos - i] != ascii::Lf; ++i, ++current_col) {
    }

    size_t new_cursor = pos, row = 0, next_col = 0;

    while(new_cursor < text.size && row <= step && next_col <= current_col) {
        if(text.data[new_cursor] == ascii::Lf) {
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

        if(text.data[new_cursor] == ascii::Lf) {
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

size_t navigation::row_start(const utils::Slice<uint8_t>& text, const size_t pos) {    
    auto i = pos == 0? pos : pos - 1;
    for(; i > 0 && text.data[i] != ascii::Lf; --i) {
    }
    
    return i == 0? i : i + 1;
}

size_t navigation::row_end(const utils::Slice<uint8_t>& text, const size_t pos) {
    auto i = pos;
    for(; i < text.size && text.data[i] != ascii::Lf; ++i) {
    }

    return i;
}