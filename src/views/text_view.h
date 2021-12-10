#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"

namespace views::text_view {
    constexpr utils::Position StartPos = utils::Position { row: 0, col: 3 };

    utils::Position render(const utils::Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer);
}

#endif