#include <cstddef>
#include <cstdint>
#include <memory>

#include "../utils/slice.h"
#include "../term/keys.h"
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

void FixedBuffer::write(const Slice<uint8_t>& slice) {
    write(slice.data, slice.size);
}

void FixedBuffer::accept(void (*visit)(const Slice<uint8_t>&)) {
    if(_size > _prelude_size) {
        const auto start = _bytes.get();

        size_t last_cr = 0, last_pos = _size - 1;
        auto pos = ScreenPosition {1, 1};
        const auto cr = slice::from(ansi::NextLine);

        // Buffer out text line by line. Carriage return are translated to VT100 LineFeed.
        for(size_t index = 0; index < _size; index++) {
            if(_bytes[index] == keys::CarriageReturn) {
                visit(Slice(start + last_cr, index - last_cr));
                visit(cr);
                last_cr = index;
                pos.row++;
            }
        }

        // Buffer out remaining text eg. in case the last line does not end in carriage return.
        if (last_cr < last_pos) {
            visit(Slice(start + last_cr, _size - last_cr));

            const auto offset = pos.row == 1? _prelude_size - 1 : 0;
            pos.col = _size - last_cr - offset;
        }

        visit(slice::from(ansi::go_to(pos)));
    }
}

void FixedBuffer::clear() {
    _size = _prelude_size;
}