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

FixedBuffer::FixedBuffer(const size_t capacity, const Slice<uint8_t>& prelude):
    _bytes(std::make_unique<uint8_t[]>(capacity)),
    _prelude_size(prelude.size),
    _size(prelude.size),
    _capacity(capacity) {

    std::copy(prelude.data, prelude.data + prelude.size, _bytes.get());
}

void FixedBuffer::write(const uint8_t* bytes, size_t size) {
    const auto new_size = _size + size;
    if(new_size < _capacity) {
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