#pragma once

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
            size_t _capacity;
            size_t _last_piece;

            PieceCursor cursor(const size_t pos);

        public:

            explicit PieceTable(const size_t capacity);
        
            size_t insert(const uint8_t v, const size_t pos);

            void erase(const size_t pos);            

            size_t size() const;

            template <typename T, void (T::*visit)(const utils::Slice<uint8_t>&)>
            void accept(T& visitor) {
                for(size_t i = 0; i < _pieces.size(); i++) {
                    const auto start = _bytes.get() + _pieces[i].start;
                    const auto slice = utils::Slice<uint8_t>(start, _pieces[i].size);
                    (visitor.*visit)(slice);
                }
            }
    };
}