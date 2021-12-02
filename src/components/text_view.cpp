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

void TextView::render(void (*write)(const utils::Slice<uint8_t>&)) {
    const auto start = _bytes.get();
    const auto line_break = Slice(ansi::NextLine.data(), ansi::NextLine.size());
    size_t last_cr = 0;

    for(auto i = 0; i < _length; ++i) {
        const auto v = start[i];
        const auto is_line_break = v == ascii::CarriageReturn;

        if(is_line_break) {
            write(Slice(start + last_cr, i - last_cr));
            write(line_break);
            last_cr = i;
        }
    }

    if (last_cr < _length) {
        write(Slice(start + last_cr, _length - last_cr));
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

void TextView::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos)) {
    _cursor = find_pos(Slice(_bytes.get(), _length), _cursor);
}

void TextView::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step), const size_t step) {
    _cursor = find_pos(Slice(_bytes.get(), _length), _cursor, step);
}

size_t TextView::length() const {
    return _length;
}