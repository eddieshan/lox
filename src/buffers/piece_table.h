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

            PieceCursor cursor(const size_t pos);

        public:

            PieceTable();
        
            size_t insert(const uint8_t v, const size_t pos);

            size_t size() const;

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