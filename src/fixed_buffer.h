#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>

#include "utils.h"

class FixedBuffer {
    private:
        std::unique_ptr<uint8_t[]> _bytes;
        size_t _size;

    public:
    
        FixedBuffer();

        void write(const uint8_t*, size_t);

        void accept(void (*visit)(utils::Slice<uint8_t>));

        void write(utils::Slice<uint8_t> data);

        void clear();
};

#endif