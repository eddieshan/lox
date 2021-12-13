#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <array>

#include "../utils/slice.h"

namespace buffers {
    class FixedBuffer {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            size_t _preamble_size;
            size_t _size;
            size_t _capacity;

        public:
        
            explicit FixedBuffer(const size_t capacity, const utils::Slice<uint8_t>& prelude);

            template<size_t size>
            void write(const std::array<uint8_t, size>& array) {
                write(array.data(), size);
            }

            void write(const uint8_t*, size_t);

            utils::Slice<uint8_t> data() const;

            void clear();
    };
}