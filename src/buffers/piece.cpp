#include <stdio.h>
#include <list>

#include "piece.h"

using namespace buffers;

PieceCursor piece_cursor::from(const size_t pos, const std::list<Piece>::iterator& begin, const std::list<Piece>::iterator& end) {
    size_t index = 0;

    for(auto piece = begin; piece != end; ++piece) {
        const auto next_index = index + piece->size;
        if(next_index < pos) {            
            index = next_index;
        } else {
            return PieceCursor { piece: piece, offset: pos - index};
        }
    }
    
    return PieceCursor { piece: end, offset: 0 };
}