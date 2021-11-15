#include <cstddef>
#include <cstdint>
#include <memory>

#include "fixed_buffer.h"

constexpr size_t BufferSize = 1024;

FixedBuffer::FixedBuffer(): 
    _size(0), 
    _bytes(std::make_unique<uint8_t[]>(BufferSize)) { 
    }

void FixedBuffer::write(const uint8_t* bytes, size_t size) {
    auto new_size = _size + size;
    if(new_size < BufferSize) {
        auto current = _bytes.get() + _size;
        std::copy(bytes, bytes + size, current);
        _size = new_size;
    }
}

void FixedBuffer::accept(void (*visit)(const void*, size_t)) {
    if(_size > 0) {
        visit(_bytes.get(), _size);
    }
}

void FixedBuffer::clear() {
    _size = 0;
}