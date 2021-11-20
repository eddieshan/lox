#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>
#include <array>

#include "utils.h"

class FixedBuffer {
    private:
        std::unique_ptr<uint8_t[]> _bytes;
        size_t _prelude_size;
        size_t _size;
        void write(const uint8_t*, size_t);

    public:
    
        FixedBuffer(const utils::Slice<uint8_t>& prelude);

        template<size_t size>
        void write(const std::array<uint8_t, size>& array) {
            write(array.data(), size);
        }

        void accept(void (*visit)(const utils::Slice<uint8_t>&));

        void write(const utils::Slice<uint8_t>& data);

        void clear();
};

#endif