#include <cstddef>
#include <cstdint>
#include <memory>

#include "gap_buffer.h"

GapBuffer::GapBuffer(): 
    _gap(0),
    _end(BufferLimit),
    _bytes(std::make_unique<uint8_t[]>(BufferSize)) {
}

void GapBuffer::insert(uint8_t byte) {
    _bytes[_gap] = byte;
    _gap += 1;
}