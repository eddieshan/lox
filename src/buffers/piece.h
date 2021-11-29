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

    class PieceCursor {
        private:
            std::list<Piece>::iterator _end;

        public:

            std::list<Piece>::iterator piece;
            size_t offset;

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