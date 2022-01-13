#pragma once

#include <cstdint>

#include "../utils/range.h"

namespace utils::ascii {
    
    constexpr auto Numbers = utils::Range<uint8_t> { start: (uint8_t)'0', end: (uint8_t)'9' };
    constexpr auto LettersUpper = utils::Range<uint8_t> { start: (uint8_t)'A', end: (uint8_t)'Z' };
    constexpr auto LettersLower = utils::Range<uint8_t> { start: (uint8_t)'a', end: (uint8_t)'z' };

    constexpr uint8_t Esc             = 27;
    constexpr uint8_t WhiteSpace      = 32;
    constexpr uint8_t Lf              = 0x0a;
    
    constexpr uint32_t CtrlO          = 0x0000000f;
    constexpr uint32_t CtrlQ          = 0x00000011;

    constexpr uint32_t Cr             = 0x0000000d;
    
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