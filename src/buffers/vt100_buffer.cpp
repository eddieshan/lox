#include <cstddef>
#include <cstring>
#include <memory>

#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../utils/slice.h"
#include "../utils/array_buffer.h"
#include "../term/ansi.h"

#include "vt100_buffer.h"

using namespace utils;
using namespace term;
using namespace buffers;

Vt100Buffer::Vt100Buffer(const size_t capacity): 
    _buffer(capacity) {}

void Vt100Buffer::esc(const uint8_t val) {
    write(ansi::Csi);

    if(_buffer.size < _buffer.capacity()) {
        _buffer.data()[_buffer.size] = val;
        ++_buffer.size;
    }
}

void Vt100Buffer::esc(const utils::Position& position) {
    write(ansi::Csi);

    constexpr auto CursorEscape = std::array<uint8_t, 8> { '\0', '\0', '\0', ';', '\0', '\0', '\0', 'H' };
    const auto remaining = _buffer.capacity() - _buffer.size;

    if(CursorEscape.size() <= remaining) {
        const auto current = _buffer.data() + _buffer.size;
        std::copy(CursorEscape.data(), CursorEscape.data() + CursorEscape.size(), current);
        convert::to_chars_3(position.row, current);
        convert::to_chars_3(position.col, current + 4);
        _buffer.size += CursorEscape.size();
    }
}

void Vt100Buffer::esc(const uint32_t val, uint8_t attr) {
    write(ansi::Csi);

    const auto seq_size = 4;
    const auto remaining = _buffer.capacity() - _buffer.size;

    if(seq_size <= remaining) {
        const auto current = _buffer.data() + _buffer.size;
        std::memset(current, 0, 3);
        convert::to_chars_3(val, current);
        current[3] = attr;
        _buffer.size += seq_size;
    }
}

void Vt100Buffer::esc(const ansi::ColorAttribute color_attr) {
    write(ansi::Csi);
    
    constexpr auto ColorEscape = std::array<uint8_t, 9> { '\0', '\0', ';', '5', ';', '\0', '\0', '\0', 'm' };
    const auto remaining = _buffer.capacity() - _buffer.size;

    if(ColorEscape.size() <= remaining) {
        const auto current = _buffer.data() + _buffer.size;

        std::copy(ColorEscape.data(), ColorEscape.data() + ColorEscape.size(), current);
        convert::to_chars_2(color_attr.attr, current);
        convert::to_chars_3(color_attr.color, current + 5);
        _buffer.size += ColorEscape.size();
    }
}

void Vt100Buffer::esc(const Slice<uint8_t>& slice) {
    write(ansi::Csi);
    write(slice);
}

void Vt100Buffer::esc(const uint8_t* data, const size_t size) {
    write(ansi::Csi);
    write(data, size);
}

void Vt100Buffer::write(const Slice<uint8_t>& slice) {
    const auto new_size = _buffer.size + slice.size;
    if(new_size < _buffer.capacity()) {
        const auto current = _buffer.data() + _buffer.size;
        std::copy(slice.data, slice.data + slice.size, current);
        _buffer.size = new_size;
    }
}

void Vt100Buffer::write(const uint8_t* data, const size_t size) {
    const auto new_size = _buffer.size + size;
    if(new_size < _buffer.capacity()) {
        const auto current = _buffer.data() + _buffer.size;
        std::copy(data, data + size, current);
        _buffer.size = new_size;
    }
}

void Vt100Buffer::write(const char* data) {
    const auto length = strlen(data);
    const auto new_size = _buffer.size + length;
    if(new_size < _buffer.capacity()) {
        const auto current = _buffer.data() + _buffer.size;
        std::copy(data, data + length, current);
        _buffer.size = new_size;
    }
}

void Vt100Buffer::clear() {
    _buffer.size = 0;
}

Slice<uint8_t> Vt100Buffer::text() const {
    return Slice(_buffer.data(), _buffer.size);
}