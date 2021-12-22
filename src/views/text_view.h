#pragma once

#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../buffers/fixed_buffer.h"

namespace views::text_view {
    constexpr utils::Position StartPos = utils::Position { row: 0, col: 4 };

    void render(const utils::Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer);
}