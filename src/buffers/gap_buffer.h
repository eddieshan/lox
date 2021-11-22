#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>

#include "../utils/slice.h"

namespace {
    constexpr size_t Kb = 1024;
    constexpr size_t BlockSize = 10*Kb;
    constexpr size_t BufferSize = 3*BlockSize;
    constexpr size_t BufferLimit = BufferSize - 1;
}


namespace buffers {
    class GapBuffer {
        private:

            std::unique_ptr<uint8_t[]> _bytes;
            size_t _gap;
            size_t _end;

            template <typename T>
            void accept(size_t from, size_t to, void (T::*visit)(const utils::Slice<uint8_t>&), T& v) {
                auto start = _bytes.get() + from;
                (v.*visit)(utils::Slice(start, to - from + 1));
            }

        public:
        
            GapBuffer();

            void insert(uint8_t);

            template <typename T>
            void accept(void (T::*visit)(const utils::Slice<uint8_t>&), T& v) {
                accept(0, _gap, visit, v);
                if(_end < BufferLimit) {
                    accept(_end + 1, BufferSize, visit, v);
                }
            }
    };
}

#endif