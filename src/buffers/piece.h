#ifndef PIECE_H
#define PIECE_H

#include <cstddef>
#include <list>

namespace buffers {

    struct Piece {
        size_t start;
        size_t size;
    };

    struct PieceCursor {
        std::list<Piece>::iterator piece;
        size_t offset;
    };

    namespace piece_cursor {
        PieceCursor from(const size_t pos, const std::list<Piece>::iterator& begin, const std::list<Piece>::iterator& end);
    }
}
#endif