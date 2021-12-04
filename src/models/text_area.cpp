#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"

#include "text_area.h"

using namespace utils;
using namespace term;
using namespace models;

TextArea::TextArea(size_t size): 
    _bytes(std::make_unique<uint8_t[]>(size)),
    _size(size),
    _length(0) {}

void TextArea::write(const utils::Slice<uint8_t>& slice) {
    const auto new_length = _length + slice.size;
    if(new_length < _size) {
        const auto current = _bytes.get() + _length;
        std::copy(slice.data, slice.data + slice.size, current);
        _length = new_length;
    }
}

void TextArea::clear() {
    _length = 0;
}

Slice<uint8_t> TextArea::text() const {
    return Slice(_bytes.get(), _length);
}

size_t TextArea::position() const {
    return _cursor;
}

void TextArea::move_to(const size_t pos) {
    if(pos >= 0 && pos < _size) {
        _cursor = pos;
    }
}

void TextArea::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos)) {
    _cursor = find_pos(Slice(_bytes.get(), _length), _cursor);
}

void TextArea::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step), const size_t step) {
    _cursor = find_pos(Slice(_bytes.get(), _length), _cursor, step);
}

size_t TextArea::length() const {
    return _length;
}