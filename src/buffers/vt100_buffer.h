#pragma once

#include <cstddef>

#include "../utils/geometry.h"
#include "../utils/array_buffer.h"
#include "../utils/slice.h"
#include "../term/ansi.h"

namespace buffers {

    class Vt100Buffer {
        private:
            utils::ArrayBuffer<uint8_t> _buffer;

        public:

            explicit Vt100Buffer(const size_t capacity);

            void esc(const uint8_t val);

            void esc(const utils::Position& position);

            void esc(const term::ansi::ColorAttribute color_attr);

            void esc(const uint32_t val, uint8_t attr);

            void esc(const utils::Slice<uint8_t>& slice);

            void esc(const uint8_t* data, const size_t size);

            void write(const utils::Slice<uint8_t>& data);

            void write(const uint8_t* data, const size_t size);

            void write(const char* data);            

            utils::Slice<uint8_t> text() const;

            void clear();
    };
}