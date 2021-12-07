#ifndef PIECE_TABLE_H
#define PIECE_TABLE_H

#include <cstddef>
#include <memory>

#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../utils/array_list.h"

#include "piece.h"

namespace buffers {

    class PieceTable {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            utils::ArrayList<Piece> _pieces;
            size_t _size;
            size_t _last_piece;

            PieceCursor cursor(const size_t pos);

        public:

            PieceTable();
        
            size_t insert(const uint8_t v, const size_t pos);

            size_t size() const;

            template <typename T>
            void accept(void (T::*visit)(const utils::Slice<uint8_t>&), T& v) {
                for(size_t i = 0; i < _pieces.size(); i++) {
                    const auto start = _bytes.get() + _pieces[i].start;
                    const auto slice = utils::Slice<uint8_t>(start, _pieces[i].size);
                    //printf("(%d, %d)", _pieces[i].start, _pieces[i].size);
                    (v.*visit)(slice);
                }
            }
    };
}

#endif