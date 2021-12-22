#pragma once

#include <cstdint>

namespace utils::ascii {

    constexpr uint8_t Esc = 27;
    constexpr uint8_t Quote = 34;
    constexpr uint8_t Zero = 48;
    constexpr uint8_t Nine = 57;

    constexpr uint32_t WhiteSpace = 32;
    
    constexpr uint32_t CtrlO          = 0x0000000f;
    constexpr uint32_t CtrlQ          = 0x00000011;

    constexpr uint32_t Cr             = 0x0000000d;
    constexpr uint32_t Lf = 10;

    constexpr uint32_t Up             = 0x00415b1b;
    constexpr uint32_t Down           = 0x00425b1b;
    constexpr uint32_t Right          = 0x00435b1b;
    constexpr uint32_t Left           = 0x00445b1b;
    constexpr uint32_t LnStart        = 0x00485b1b;
    constexpr uint32_t LnEnd          = 0x00465b1b;

    constexpr uint32_t Htab           = 0x09000000;
    constexpr uint32_t Del            = 0x7e335b1b;
    constexpr uint32_t BSpace         = 0x0000007f;

}