#pragma once

#include <cstdint>

namespace utils {

    struct Range {
        uint8_t start;
        uint8_t end;
    };
    
    namespace range {
        bool contains(const Range& range, const uint8_t val);
    }
}