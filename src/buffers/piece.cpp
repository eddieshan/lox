#include <stdio.h>

#include "../utils/slice.h"
#include "piece.h"

using namespace buffers;

PieceCursor piece_cursor::from(const size_t pos, const utils::Slice<Piece>& pieces) {
    size_t count = 0;

    for(size_t i = 0; i < pieces.size; ++i) {
        const auto next_count = count + pieces.data[i].size;
        if(next_count == 0) {
            return PieceCursor { pos: 0, offset: 0 };
        } else if(next_count < pos + 1) {
            count = next_count;
        } else {
            return PieceCursor { pos: i, offset: pos - count };
        }
    }
    
    return PieceCursor { pos: pieces.size, offset: 0 };
}