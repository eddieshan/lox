#pragma once

#include <cstddef>
#include "../utils/slice.h"

namespace buffers {

    struct Piece {
        size_t start;
        size_t size;
    };

    struct PieceCursor {
        size_t pos;
        size_t offset;
    };

    namespace piece_cursor {
        PieceCursor from(const size_t pos, const utils::Slice<Piece>& pieces);
    }
}