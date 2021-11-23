#ifndef KEYS_H
#define KEYS_H

#include <cstdint>

namespace utils::ascii {

    constexpr uint32_t WhiteSpace = 32;
    constexpr uint32_t LnFeed = 10;
    
    constexpr uint32_t CarriageReturn = 0x0000000d;

    constexpr uint32_t CtrlQ          = 0x00000011;
    constexpr uint32_t Cr             = 0x0d000000;
    constexpr uint32_t BSpace         = 0x7f000000;
    constexpr uint32_t Up             = 0x00415b1b;
    constexpr uint32_t Down           = 0x00425b1b;
    constexpr uint32_t Right          = 0x00435b1b;
    constexpr uint32_t Left           = 0x00445b1b;
    constexpr uint32_t Htab           = 0x09000000;
    constexpr uint32_t LnStart        = 0x1b5b4800;
    constexpr uint32_t LnEnd          = 0x1b5b4600;
    constexpr uint32_t Del            = 0x1b5b337e;
}

#endif