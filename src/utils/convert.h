#pragma once

#include <cstdint>
#include <cstddef>

namespace utils::convert {
    void to_chars_3(const size_t val, uint8_t* target);
    void to_chars_2(const size_t val, uint8_t* target);
}