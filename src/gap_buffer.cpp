#include <cstddef>
#include <cstdint>
#include <memory>

#include "gap_buffer.h"

GapBuffer::GapBuffer() {
    _bytes = std::make_unique<uint8_t[]>(BufferSize);
    _gap = 0;
    _end = BufferLimit;
}

void GapBuffer::insert(uint8_t byte) {
    _bytes[_gap] = byte;
    _gap += 1;
}