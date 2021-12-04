#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"

#include "text_view.h"
#include "cursor.h"

using namespace utils;
using namespace term;
using namespace views;

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

void TextView::render(buffers::FixedBuffer& buffer) {
    const auto start = _bytes.get();
    size_t last_cr = 0, row = 1;

    constexpr auto move_to_start_col = array::from<uint8_t>((uint8_t)'3', (uint8_t)'C');
    constexpr auto next_line = array::concat(ansi::NextLine, ansi::Csi, move_to_start_col);

    buffer.write(ansi::Csi);
    buffer.write(move_to_start_col);

    for(auto i = 0; i < _length; ++i) {
        if(start[i] == ascii::CarriageReturn) {
            const auto offset = last_cr == 0? 0 : 1;
            buffer.write(start + last_cr + offset, i - last_cr);
            last_cr = i;
            ++row;
            buffer.write(next_line);
        }
    }

    if (last_cr < _length) {
        const auto offset = last_cr == 0? 0 : 1;
        buffer.write(start + last_cr + offset, _length - last_cr);
    }

    std::array<uint8_t, 3> line_count = { 0, 0, 0 };

    buffer.write(ansi::Home);
    
    for(auto i = 1; i <= row; ++i) {
        std::to_chars((char*)line_count.data(), (char*)line_count.data() + line_count.size() - 1, i);
        buffer.write(line_count);
        buffer.write(ansi::NextLine);
    }
}

void TextView::clear() {
    _length = 0;
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