#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "navigation.h"

using namespace utils;
using namespace text;

utils::Position navigation::text_cursor(const Slice<uint8_t>& text, const size_t pos) {
    auto cursor = Position { 0, 0 };

    for(auto i = 0; i < pos; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;

        if(is_line_break) {
            ++cursor.row;
            cursor.col = 0;
        } else {
            ++cursor.col;
        }
    }

    return cursor;
}

size_t navigation::col::right(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos < text.size? pos + 1 : pos;
}

size_t navigation::col::left(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos > 0? pos - 1 : pos;
}

size_t navigation::row::down(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step) {
    const auto line_above_end = pos == 0? 0 : slice::find_back(text, ascii::Lf, pos - 1);
    const auto line_end = slice::find(text, ascii::Lf, pos);
    const auto line_below_end = slice::find(text, ascii::Lf, line_end + 1);
    const auto distance_to_start = pos - line_above_end;

    const auto offset = line_above_end == 0? 1 : 0;
    const auto new_pos = line_end + distance_to_start + offset;

    return std::min(new_pos, line_below_end);
}

size_t navigation::row::up(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step) {
    if(pos <= 1) {
        return 0;
    } else {
        const auto line_above_end = slice::find_back(text, ascii::Lf, pos - 1);
        const auto line_above_start = slice::find_back(text, ascii::Lf, line_above_end - 1);
        const auto distance_to_start = pos - line_above_end;

        const auto offset = line_above_start == 0? 1 : 0;
        const auto new_pos = line_above_start + distance_to_start - offset;

        return std::min(new_pos, line_above_end);
    }
}

size_t navigation::row::start(const utils::Slice<uint8_t>& text, const size_t pos) {
    return pos == 0? 0 : slice::find_back(text, ascii::Lf, pos - 1) + 1;
}

size_t navigation::row::end(const utils::Slice<uint8_t>& text, const size_t pos) {
    return slice::find(text, ascii::Lf, pos);
}