#ifndef PIECE_TABLE_H
#define PIECE_TABLE_H

#include <cstddef>
#include <memory>

#include "utils.h"

struct Piece {
    size_t start;
    size_t size;
};

class PieceTable {
    private:
        std::unique_ptr<uint8_t[]> _bytes;
        std::unique_ptr<Piece[]> _pieces;
        size_t _size;
        size_t _n_pieces;

    public:

        PieceTable();
    
        void insert(uint8_t);

        template <typename T>
        void accept(void (T::*visit)(const utils::Slice<uint8_t>&), T& v) {
            for(auto i = 0; i < _n_pieces; i++) {
                auto start = _bytes.get() + _pieces[i].start;
                auto slice = utils::Slice(start, _pieces[i].size);
                (v.*visit)(slice);
            }
        }
};


#endif