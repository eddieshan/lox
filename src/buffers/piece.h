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

        void forward(const size_t size);

        bool is_first();

        bool is_last(const size_t size);

        bool is_at_end(const size_t size);
    };
}
#endif