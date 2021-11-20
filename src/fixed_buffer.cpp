#include <cstddef>
#include <cstdint>
#include <memory>

#include "fixed_buffer.h"
#include "utils.h"

constexpr size_t BufferSize = 1024;

FixedBuffer::FixedBuffer(const utils::Slice<uint8_t>& prelude):
    _size(prelude.size),
    _prelude_size(prelude.size),
    _bytes(std::make_unique<uint8_t[]>(BufferSize)) {

    std::copy(prelude.data, prelude.data + prelude.size, _bytes.get());
}

void FixedBuffer::write(const uint8_t* bytes, size_t size) {
    auto new_size = _size + size;
    if(new_size < BufferSize) {
        auto current = _bytes.get() + _size;
        std::copy(bytes, bytes + size, current);
        _size = new_size;
    }
}

void FixedBuffer::write(const utils::Slice<uint8_t>& slice) {
    write(slice.data, slice.size);
}

void FixedBuffer::accept(void (*visit)(const utils::Slice<uint8_t>&)) {
    if(_size > 0) {
        visit(utils::Slice(_bytes.get(), _size));
    }
}

void FixedBuffer::clear() {
    _size = _prelude_size;
}