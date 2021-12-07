#include <cstddef>
#include <memory>

#include "../utils/units.h"
#include "../utils/array_list.h"
#include "../utils/geometry.h"
#include "piece_table.h"

using namespace buffers;
using namespace utils;

PieceTable::PieceTable(const size_t capacity):
    _bytes(std::make_unique<uint8_t[]>(capacity)),
    _pieces(units::Kb),
    _size(0),
    _capacity(capacity),
    _last_piece(0) {
        _pieces.insert({ start: 0, size: 0 });
    }

size_t PieceTable::insert(const uint8_t v, const size_t pos) {

    if(_size < _capacity) {
        if(pos == 0 || pos == _size) {
            ++_pieces[_last_piece].size;
        } else {
            auto cursor = piece_cursor::from(pos, _pieces.data());
            const auto piece = &_pieces[cursor.pos];
            const auto index = piece->start + cursor.offset;

            const auto piece_right = Piece { start: index, size: piece->size - cursor.offset };
            const auto new_piece = Piece { start: _size, size: 1 };

            piece->size = cursor.offset;

            const auto new_pos = cursor.pos + 1;

            _pieces.insert(piece_right, new_pos);
            _pieces.insert(new_piece, new_pos);

            _last_piece = new_pos;
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