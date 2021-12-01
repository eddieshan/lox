#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"
#include "text_view.h"

using namespace utils;
using namespace term;
using namespace components;

TextView::TextView(size_t size): 
    _bytes(std::make_unique<uint8_t[]>(size)),
    _size(size),
    _length(0) {}

void TextView::write(const utils::Slice<uint8_t>& slice) {
    const auto new_length = _length + slice.size;
    if(new_length < _size) {
        const auto current = _bytes.get() + _length;
        std::copy(slice.data, slice.data + slice.size, current);
        _length = new_length;
    }
}

void TextView::render(void (*visit)(const utils::Slice<uint8_t>&)) {
    const auto start = _bytes.get();
    const auto line_break = Slice(ansi::NextLine.data(), ansi::NextLine.size());
    size_t last_cr = 0;

    for(auto i = 0; i < _length; ++i) {
        const auto v = start[i];
        const auto is_line_break = v == ascii::CarriageReturn;

        if(is_line_break) {
            visit(Slice(start + last_cr, i - last_cr));
            visit(line_break);
            last_cr = i;
        }
    }

    if (last_cr < _length) {
        visit(Slice(start + last_cr, _length - last_cr));
    }
}

void TextView::clear() {
    _length = 0;
}

Position TextView::screen_position() const {
    const auto start = _bytes.get();
    auto pos = Position { 0, 0 };
    size_t last_cr = 0;

    for(auto i = 0; i < _cursor; ++i) {
        const auto v = start[i];
        const auto is_line_break = v == ascii::CarriageReturn;

        if(is_line_break) {
            ++pos.row;
            pos.col = 0;
        } else {
            ++pos.col;
        }
    }

    return pos;
}

size_t TextView::position() const {
    return _cursor;
}

void TextView::move_to(const size_t pos) {
    if(pos >= 0 && pos < _size) {
        _cursor = pos;
    }
}

size_t TextView::length() const {
    return _length;
}

void TextView::col_forward() {
    if(_cursor < _length - 1) {
        ++_cursor;
    }
}

void TextView::col_back() {
    if(_cursor > 0) {
        --_cursor;
    }
}

void TextView::row_forward(const size_t step) {
    const auto start = _bytes.get();
    size_t last_cr = 0;
    size_t col = 0;

    for(auto i = 1; i <= _cursor && start[_cursor - i] != ascii::CarriageReturn; ++i, ++col) {
    }

    auto new_cursor = _cursor + 1;

    for(auto row = 0; new_cursor < _length && row < step; ++new_cursor) {
        if(start[new_cursor] == ascii::CarriageReturn) {
            ++row;
        }
    }

    for(auto n_cols = 0; new_cursor < _length && n_cols < col; ++new_cursor, ++n_cols) {
        if(start[new_cursor] == ascii::CarriageReturn) {
            break;
        }
    }

    _cursor = new_cursor < _length? new_cursor : _length - 1;
}

void TextView::row_back(const size_t step) {

    const auto start = _bytes.get();
    size_t row = 0, line_size = 0, prev_line_size = 0, new_cursor = _cursor;

    while(new_cursor > 0 && row <= step) {
        --new_cursor;

        if(start[new_cursor] == ascii::CarriageReturn) {
            ++row;
        }

        if(row == 0) {
            ++line_size;
        } else if(row == 1) {
            ++prev_line_size;
        }
    }

    const auto capped = line_size > prev_line_size? prev_line_size - 1: line_size;
    _cursor = new_cursor + capped;
}