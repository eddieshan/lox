#ifndef CURSOR_H
#define CURSOR_H

#include "../utils/geometry.h"

namespace components::cursor {
    // Writes a VT100 sequence to move the cursor to the desired screen position.
    // The screen position is required to be zero based.
    // VT100 screen coordinates are 1 based so row and col are incremented by 1.
    void render(const utils::Position& pos, void (*visit)(const utils::Slice<uint8_t>&));
}

#endif
