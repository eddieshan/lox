#ifndef TERM_H
#define TERM_H

#include <cstdint>
#include <cstddef>

#include "utils.h"

namespace term {

    struct Key {
        uint32_t code;
        size_t size;
    };

    enum class RawModeResult {
        Ok,
        InvalidTty,
        FailedToRetrieveTermAttr,
        FailedToSetRawAttr
    };

    RawModeResult enable_raw_mode();
    Key read_key();
    void write_bytes(const utils::Slice<uint8_t>& buffer);
    void flush();

}
#endif