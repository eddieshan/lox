#pragma once

#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"

namespace views::text_view {
    constexpr utils::Position StartPos = utils::Position { row: 0, col: 4 };

    models::TextState render(const utils::Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer);
}