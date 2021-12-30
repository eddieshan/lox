#include <cstdint>
#include "range.h"

using namespace utils;

bool range::contains(const Range& range, const uint8_t val) {
    return val >= range.start && val <= range.end;
}