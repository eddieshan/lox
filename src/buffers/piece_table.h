#pragma once

#include <cstddef>

#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../utils/array_list.h"

#include "piece.h"

namespace buffers {

    class PieceTable {
        private:
            utils::ArrayBuffer<uint8_t> _buffer;
            utils::ArrayList<Piece> _pieces;
            size_t _last_piece;

            PieceCursor cursor(const size_t pos);

        public:

            explicit PieceTable(const size_t capacity);
        
            size_t insert(const uint8_t v, const size_t pos);

            void append(const utils::Slice<uint8_t>& data);

            void erase(const size_t pos);

            void clear();

            size_t size() const;

            size_t capacity() const;

            template <typename T, void (T::*visit)(const utils::Slice<uint8_t>&)>
            void accept(T& visitor) {
                for(auto i = 0; i < _pieces.size(); i++) {
                    const auto start = _buffer.data() + _pieces[i].start;
                    const auto slice = utils::Slice<uint8_t>(start, _pieces[i].size);
                    (visitor.*visit)(slice);
                }
            }
    };
}