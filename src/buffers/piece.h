#ifndef PIECE_H
#define PIECE_H

#include <cstddef>
#include <list>

namespace buffers {

    struct Piece {
        size_t start;
        size_t size;
        size_t line_count;
    };

    struct PieceCursor {
        std::list<Piece>::iterator piece;
        size_t offset;
        std::list<Piece>::iterator end;

        PieceCursor() = default;

        PieceCursor(std::list<Piece> &pieces);

        size_t index();        

        void back();

        void forward();

        bool is_first();

        bool is_last();

        bool end_of_piece();
    };
}
#endif