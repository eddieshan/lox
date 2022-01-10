#include <cstddef>

#include "../utils/units.h"
#include "../utils/array_list.h"
#include "../utils/geometry.h"
#include "piece_table.h"

using namespace buffers;
using namespace utils;

PieceTable::PieceTable(const size_t capacity):
    _buffer(capacity),
    _pieces(units::Kb),
    _last_piece(0) {
        _pieces.insert({ start: 0, size: 0 });
    }

size_t PieceTable::insert(const uint8_t v, const size_t pos) {

    if(_buffer.size < _buffer.capacity()) {
        if(pos == _buffer.size) {
            ++_pieces[_last_piece].size;
        } else {
            const auto cursor = piece_cursor::from(pos, _pieces.data());
            const auto piece = &_pieces[cursor.pos];
            const auto new_piece = Piece { start: _buffer.size, size: 1 };

            if(cursor.offset == 0) {
                _pieces.insert(new_piece, cursor.pos);
                _last_piece = cursor.pos;
            } else {
                const auto index = piece->start + cursor.offset;
                const auto piece_right = Piece { start: index, size: piece->size - cursor.offset };

                piece->size = cursor.offset;

                const auto new_pos = cursor.pos + 1;

                _pieces.insert(piece_right, new_pos);
                _pieces.insert(new_piece, new_pos);

                _last_piece = new_pos;
            }
        }

        _buffer.data()[_buffer.size] = v;
        ++_buffer.size;

        return pos + 1;
    } else {
        return 0;
    }
}

void PieceTable::append(const Slice<uint8_t>& data) {

    const auto remaining = _buffer.capacity() - _buffer.size;

    if(data.size <= remaining) {
        std::copy(data.data, data.data + data.size, _buffer.data() + _buffer.size);
        _pieces[_last_piece].size += data.size;
        _buffer.size += data.size;
    }
}

void PieceTable::erase(const size_t pos) {
    if(_buffer.size > 0 && pos < _buffer.size) {
        auto cursor = piece_cursor::from(pos, _pieces.data());
        const auto piece = &_pieces[cursor.pos];

        if(cursor.offset == 0) {
            ++piece->start;
            --piece->size;
        } else if(cursor.offset == piece->size - 1) {
            --piece->size;
        } else {
            const auto new_size = cursor.offset;
            const auto right_start = piece->start + new_size + 1;
            const auto piece_right = Piece { start: right_start, size: piece->size - cursor.offset - 1 };

            piece->size = new_size;

            const auto new_pos = cursor.pos + 1;
            _pieces.insert(piece_right, new_pos);

            _last_piece = new_pos;
        }
    }
}

void PieceTable::clear() {
    _pieces.clear();
    _buffer.size = 0;
    _last_piece = 0;
    _pieces.insert({ start: 0, size: 0 });
}

size_t PieceTable::size() const {
    return _buffer.size;
}

size_t PieceTable::capacity() const {
    return _buffer.capacity();
}