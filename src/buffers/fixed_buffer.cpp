#include <cstddef>
#include <cstdint>
#include <memory>

#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"
#include "../term/term.h"
#include "fixed_buffer.h"

using namespace buffers;
using namespace utils;
using namespace term;

constexpr size_t BufferSize = 1024;

FixedBuffer::FixedBuffer(const Slice<uint8_t>& prelude):
    _size(prelude.size),
    _prelude_size(prelude.size),
    _bytes(std::make_unique<uint8_t[]>(BufferSize)) {

    std::copy(prelude.data, prelude.data + prelude.size, _bytes.get());
}

void FixedBuffer::write(const uint8_t* bytes, size_t size) {
    const auto new_size = _size + size;
    if(new_size < BufferSize) {
        const auto current = _bytes.get() + _size;
        std::copy(bytes, bytes + size, current);
        _size = new_size;
    }
}

void FixedBuffer::accept(void (*visit)(const Slice<uint8_t>&)) {
    visit(Slice(_bytes.get(), _size));
}

void FixedBuffer::clear() {
    _size = _prelude_size;
}