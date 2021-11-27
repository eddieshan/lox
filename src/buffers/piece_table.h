#ifndef PIECE_TABLE_H
#define PIECE_TABLE_H

#include <cstddef>
#include <memory>
#include <list>

#include "../utils/slice.h"
#include "../utils/geometry.h"

#include "piece.h"

namespace buffers {

    class PieceTable {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            std::list<Piece> _pieces;
            size_t _size;
            PieceCursor _cursor;

            bool is_linebreak(const size_t offset);
            size_t distance_to_line_start();

        public:

            PieceTable();
        
            void insert(const uint8_t);

            void col_forward();

            void col_back();

            void row_forward(const size_t step = 1);

            void row_back(const size_t step = 1);            

            utils::Position position();

            template <typename T>
            void accept(void (T::*visit)(const utils::Slice<uint8_t>&), T& v) {
                for(const auto piece : _pieces) {
                    const auto start = _bytes.get() + piece.start;
                    const auto slice = utils::Slice(start, piece.size);
                    (v.*visit)(slice);
                }
            }
    };
}

#endif