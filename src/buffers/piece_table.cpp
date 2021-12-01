#include <cstddef>
#include <memory>
#include <algorithm>

#include "../utils/units.h"
#include "../utils/geometry.h"
#include "../utils/ascii.h"
#include "piece_table.h"

using namespace buffers;
using namespace utils;

constexpr size_t BlockSize = 10*units::Kb;
constexpr size_t BufferSize = 3*BlockSize;
constexpr size_t BufferLimit = BufferSize - 1;

PieceTable::PieceTable():
    _bytes(std::make_unique<uint8_t[]>(BufferSize)),
    _pieces({{ start: 0, size: 0 }}),
    _size(0) {}

size_t PieceTable::insert(const uint8_t v, const size_t pos) {

    if(_size < BufferLimit) {
        auto current_cursor = piece_cursor::from(pos, _pieces.begin(), _pieces.end());

        const auto index = current_cursor.piece->start + current_cursor.offset;

        if(index == 0 || index == _size) {
            if(current_cursor.piece->size == 0) {
                current_cursor.piece->size = 2;
            } else {
                current_cursor.piece->size += 1;
            }

            current_cursor.offset += 1;

        } else {
            const auto piece_right = Piece { start: index, size: current_cursor.piece->size - current_cursor.offset - 1 };
            const auto new_piece = Piece { start: _size, size: 2 };            

            current_cursor.piece->size = current_cursor.offset;

            const auto next  = std::next(current_cursor.piece);
            const auto inserted = _pieces.insert(next, new_piece);
            _pieces.insert(next, piece_right);

            current_cursor.piece = inserted;
            current_cursor.offset = 1;
        }

        _bytes[_size] = v;
        ++_size;

        return pos + 1;
    } else {
        return 0;
    }
}

size_t PieceTable::size() const {
    return _size;
}