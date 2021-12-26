#include <cstring>
#include "slice.h"

using namespace utils;

Slice<uint8_t> slice::from(const char* val) {
    const auto size = std::strlen(val);
    return Slice((uint8_t*)val, size);
}