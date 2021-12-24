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
    _preamble_size(prelude.size),
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

void FixedBuffer::write(const Slice<uint8_t>& slice) {
    write(slice.data, slice.size);
}

void FixedBuffer::write_n(const uint8_t val, size_t n) {
    const auto new_size = _size + n;
    if(new_size < _capacity) {
        const auto current = _bytes.get() + _size;
        std::memset(current, val, n);
        _size = new_size;
    }
}

Slice<uint8_t> FixedBuffer::data() const {
    return Slice(_bytes.get(), _size);
}

void FixedBuffer::clear() {
    _size = _preamble_size;
}