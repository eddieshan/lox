#ifndef TERM_H
#define TERM_H

#include <cstdint>
#include <cstddef>

namespace term {

    struct Key {
        uint32_t code;
        std::size_t size;
    };

    enum class RawModeResult {
        Ok,
        InvalidTty,
        FailedToRetrieveTermAttr,
        FailedToSetRawAttr
    };

    RawModeResult enable_raw_mode();
    Key read_key();
    void write_bytes(char* buffer, std::size_t size);
    void flush();

}
#endif