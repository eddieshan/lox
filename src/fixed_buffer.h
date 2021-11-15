#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>

class FixedBuffer {
    private:
        std::unique_ptr<uint8_t[]> _bytes;
        size_t _size;

    public:
    
        FixedBuffer();

        void write(const uint8_t*, size_t);

        void accept(void (*visit)(const void*, size_t));

        void clear();
};

#endif