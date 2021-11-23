#ifndef TERM_H
#define TERM_H

#include <cstdint>
#include <cstddef>

#include "../utils/slice.h"
#include "../utils/geometry.h"

namespace term {

    struct Key {
        const uint32_t code;
        const size_t size;

        Key(uint32_t code_, size_t size_);
    };

    // struct WindowSize {
    //     unsigned int rows;
    //     unsigned int cols;
    // };

    // struct ScreenPosition {
    //     unsigned int row;
    //     unsigned int col;
    // };    

    enum class RawModeResult {
        Ok,
        InvalidTty,
        FailedToRetrieveTermAttr,
        FailedToSetRawAttr
    };

    RawModeResult enable_raw_mode();
    Key read_key();
    utils::WindowSize get_window_size();
    void write_bytes(const utils::Slice<uint8_t>& buffer);
    void flush();

}
#endif