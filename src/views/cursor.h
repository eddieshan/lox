#pragma once

#include "../utils/geometry.h"
#include "../buffers/fixed_buffer.h"

namespace views::cursor {
    // Writes a VT100 sequence to move the cursor to the desired screen position.
    // The screen position is required to be zero based.
    // VT100 screen coordinates are 1 based so row and col are incremented by 1.
    void render(const utils::Position& pos, buffers::FixedBuffer& buffer);
}