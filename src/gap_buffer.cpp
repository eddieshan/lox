#include <cstdint>
#include <memory>

#include "gap_buffer.h"

constexpr std::size_t Kb = 1024;
constexpr std::size_t BlockSize = 10*Kb;
constexpr std::size_t BufferSize = 3*BlockSize;
constexpr std::size_t BufferLimit = BufferSize - 1;

GapBuffer::GapBuffer() {
    _bytes = std::make_unique<uint8_t[]>(BufferSize);
    _gap = 0;
    _end = BufferLimit;
}

void GapBuffer::right() {
}

void GapBuffer::left() {
}

void GapBuffer::up() {

}

void GapBuffer::down() {

}

void GapBuffer::insert(uint8_t byte) {
    _bytes[_gap] = byte;
    _gap += 1;
}

void GapBuffer::ln_start() {

}

void GapBuffer::ln_end() {

}

void GapBuffer::del_right() {

}

void GapBuffer::del_left() {

}

void GapBuffer::visit(size_t from, size_t to, void (*f)(const void*, size_t))  {
    auto start = _bytes.get() + from;
    f(start, to - from + 1);
}

void GapBuffer::visit(void (*f)(const void*, size_t))  {
    visit(0, _gap, f);
    if(_end < BufferLimit) {
        visit(_end + 1, BufferSize, f);
    }
}