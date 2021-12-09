#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"

#include "text_area.h"

using namespace utils;
using namespace term;
using namespace models;

TextArea::TextArea(size_t capacity): 
    _bytes(std::make_unique<uint8_t[]>(capacity)),
    _capacity(capacity),
    _size(0),
    _cursor(0) {}

void TextArea::write(const utils::Slice<uint8_t>& slice) {
    const auto new_size = _size + slice.size;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::copy(slice.data, slice.data + slice.size, current);
        _size = new_size;
    }
}

void TextArea::clear() {
    _size = 0;
}

Slice<uint8_t> TextArea::text() const {
    return Slice(_bytes.get(), _size);
}

size_t TextArea::position() const {
    return _cursor;
}

void TextArea::move_to(const size_t pos) {
    if(pos >= 0 && pos <= _size) {
        _cursor = pos;
    }
}

void TextArea::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos)) {
    _cursor = find_pos(Slice(_bytes.get(), _size), _cursor);
}

void TextArea::move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step), const size_t step) {
    _cursor = find_pos(Slice(_bytes.get(), _size), _cursor, step);
}

size_t TextArea::size() const {
    return _size;
}