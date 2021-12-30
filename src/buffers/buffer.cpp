#include <cstddef>
#include <cstring>
#include <memory>

#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../utils/slice.h"
#include "../term/ansi.h"

#include "buffer.h"

using namespace utils;
using namespace term;
using namespace buffers;

Buffer::Buffer(const size_t capacity): 
    _bytes(std::make_unique<uint8_t[]>(capacity)),
    _capacity(capacity),
    _size(0) {}

void Buffer::esc(const uint8_t val) {
    write(ansi::Csi);

    if(_size < _capacity) {
        _bytes.get()[_size] = val;
        ++_size;
    }
}

void Buffer::esc(const utils::Position& position) {
    write(ansi::Csi);

    const auto seq_size = 8;
    const auto remaining = _capacity - _size;

    if(seq_size <= remaining) {
        const auto current = _bytes.get() + _size;
        std::memset(current, 0, 8);
        convert::to_chars_3(position.row, current);
        convert::to_chars_3(position.col, current + 4);
        current[3] = (uint8_t)';';
        current[7] = ansi::Home;
        _size += seq_size;
    }
}

void Buffer::esc(const uint32_t val, uint8_t attr) {
    write(ansi::Csi);

    const auto seq_size = 4;
    const auto remaining = _capacity - _size;

    if(seq_size <= remaining) {
        const auto current = _bytes.get() + _size;
        std::memset(current, 0, 3);
        convert::to_chars_3(val, current);
        current[3] = attr;
        _size += seq_size;
    }
}

void Buffer::esc(const Slice<uint8_t>& slice) {
    write(ansi::Csi);
    write(slice);
}

void Buffer::esc(const uint8_t* data, const size_t size) {
    write(ansi::Csi);
    write(data, size);
}

void Buffer::write(const Slice<uint8_t>& slice) {
    const auto new_size = _size + slice.size;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::copy(slice.data, slice.data + slice.size, current);
        _size = new_size;
    }
}

void Buffer::write(const uint8_t* data, const size_t size) {
    const auto new_size = _size + size;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::copy(data, data + size, current);
        _size = new_size;
    }
}

void Buffer::write(const char* data) {
    const auto length = strlen(data);
    const auto new_size = _size + length;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::copy(data, data + length, current);
        _size = new_size;
    }
}

void Buffer::clear() {
    _size = 0;
}

Slice<uint8_t> Buffer::text() const {
    return Slice(_bytes.get(), _size);
}

size_t Buffer::size() const {
    return _size;
}

size_t Buffer::capacity() const {
    return _capacity;
}