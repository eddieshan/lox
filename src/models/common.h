#pragma once

#include <cstddef>
#include <cstdint>

#include "../utils/slice.h"

namespace models {
    using Navigator = size_t (*)(const utils::Slice<uint8_t>& text, const size_t current_pos);
    using StepNavigator = size_t (*)(const utils::Slice<uint8_t>& text, const size_t current_pos, const size_t step);
}