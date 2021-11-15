#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>

namespace {
    constexpr size_t Kb = 1024;
    constexpr std::size_t BlockSize = 10*Kb;
    constexpr std::size_t BufferSize = 3*BlockSize;
    constexpr std::size_t BufferLimit = BufferSize - 1;
}

class GapBuffer {
    private:

        std::unique_ptr<uint8_t[]> _bytes;
        std::size_t _gap;
        std::size_t _end;

        template <typename T>
        void accept(size_t from, size_t to, void (T::*write)(const uint8_t*, size_t), T& v) {
            auto start = _bytes.get() + from;
            v.write(start, to - from + 1);
        }

    public:
    
        GapBuffer();

        void insert(uint8_t);

        template <typename T>
        void accept(void (T::*write)(const uint8_t*, size_t), T& v) {
            accept(0, _gap, write, v);
            if(_end < BufferLimit) {
                accept(_end + 1, BufferSize, write, v);
            }
        }
};

#endif