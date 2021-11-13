#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <memory>

class GapBuffer {
    private:
        std::unique_ptr<uint8_t[]> _bytes;
        std::size_t _gap;
        std::size_t _end;

    public:
    
        GapBuffer();

        void right();

        void left();

        void up();

        void down();

        void insert(uint8_t);
        
        void ln_start();

        void ln_end();

        void del_right();

        void del_left();
};

#endif