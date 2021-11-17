#include <cstddef>
#include <memory>

#include "piece_table.h"

constexpr size_t Kb = 1024;
constexpr size_t BlockSize = 10*Kb;
constexpr size_t BufferSize = 3*BlockSize;
constexpr size_t BufferLimit = BufferSize - 1;

PieceTable::PieceTable():
    _bytes(std::make_unique<uint8_t[]>(BufferSize)),
    _pieces(std::make_unique<Piece[]>(BufferSize)),
    _size(0),
    _n_pieces(0) { }

void PieceTable::insert(uint8_t v) {
    _bytes[_size] = v;
    _size += 1;

    _n_pieces = 1;
    _pieces[_n_pieces - 1].size += 1;
}
