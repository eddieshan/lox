#include <cstddef>
#include <cstring>
#include <memory>

#include "../utils/slice.h"

#include "buffer.h"

using namespace utils;
using namespace buffers;

Buffer::Buffer(size_t capacity): 
    _bytes(std::make_unique<uint8_t[]>(capacity)),
    _capacity(capacity),
    _size(0) {}

void Buffer::write(const utils::Slice<uint8_t>& slice) {
    const auto new_size = _size + slice.size;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::copy(slice.data, slice.data + slice.size, current);
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