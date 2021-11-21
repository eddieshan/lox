#include <cstddef>
#include <cstdint>
#include <memory>

#include "../utils/slice.h"
#include "../term/keys.h"
#include "../term/ansi.h"
#include "../term/term.h"
#include "fixed_buffer.h"

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
        const auto start = _bytes.get();
        size_t index = 0, last_cr = 0, last_pos = _size - 1;
        const auto cr = utils::slice::from(term::ansi::NextLine);

        // Buffer out text line by line. Carriage return are translated to VT100 LineFeed.
        while(index < _size) {
            if(_bytes[index] == keys::CarriageReturn) {
                visit(utils::Slice(start + last_cr, index - last_cr));
                visit(cr);
                last_cr = index;
            }

            index++;
        }

        // Buffer out remaining text eg. in case the last line does not end in carriage return.
        if (last_cr < last_pos) {
            visit(utils::Slice(start + last_cr, _size - last_cr));
        }
    }
}

void FixedBuffer::clear() {
    _size = _prelude_size;
}