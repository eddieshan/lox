#pragma once

#include <cstddef>
#include <memory>

#include "../utils/slice.h"

namespace buffers {

    class Buffer {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            size_t _capacity;
            size_t _size;

        public:

            explicit Buffer(const size_t capacity);

            void write(const utils::Slice<uint8_t>& data);

            void write(const uint8_t* data, const size_t size);

            void write(const char* data);            

            utils::Slice<uint8_t> text() const;

            void clear();

            size_t size() const;

            size_t capacity() const;
    };
}