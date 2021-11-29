#include <cstddef>
#include <memory>
#include <algorithm>

#include "../utils/geometry.h"
#include "../utils/ascii.h"
#include "piece_table.h"

using namespace buffers;
using namespace utils;

constexpr size_t Kb = 1024;
constexpr size_t BlockSize = 10*Kb;
constexpr size_t BufferSize = 3*BlockSize;
constexpr size_t BufferLimit = BufferSize - 1;


PieceTable::PieceTable():
    _bytes(std::make_unique<uint8_t[]>(BufferSize)),
    _pieces({{ start: 0, size: 0 }}),
    _size(0) {
        // _cursor gets initialized here for the second time to avoid relying 
        // in the member declaration order since it's dependent on _pieces.
        // TODO: 
        //  dependencies probably need to be restructured to have a clean initialization.       
        _cursor = PieceCursor(_pieces);
    }

bool PieceTable::is_linebreak(const size_t index) {
    return _bytes[index] == ascii::CarriageReturn;
}

size_t PieceTable::distance_to_line_start() {
    auto temp_cursor = _cursor;
    size_t line_size = 0;

    while(!temp_cursor.is_first()) {
        temp_cursor.back();
        if(is_linebreak(temp_cursor.index())) {
            break;
        } else {
            ++line_size;
        }
    }

    return line_size;
}

void PieceTable::insert(const uint8_t v) {
    if(_size < BufferLimit) {

        if(_cursor.end_of_piece()) {
            if(_cursor.piece->size == 0) {
                _cursor.piece->size = 2;
            } else {
                _cursor.piece->size += 1;
            }

            _cursor.offset += 1;
        } else {
            const auto piece_right = Piece { start: _cursor.index(), size: _cursor.piece->size - _cursor.offset - 1 };
            const auto new_piece = Piece { start: _size, size: 2, line_count: 0 };

            _cursor.piece->size = _cursor.offset;

            const auto next  = std::next(_cursor.piece);
            const auto inserted = _pieces.insert(next, new_piece);
            _pieces.insert(next, piece_right);
            
            _cursor.piece = inserted;
            _cursor.offset = 1;
        }

        _bytes[_size] = v;
        ++_size;

        if(v == ascii::CarriageReturn) {
            ++_cursor.piece->line_count;
        }
    }
}

void PieceTable::col_forward() {
    if(!_cursor.is_last()) {
        _cursor.forward();
    }
}

void PieceTable::col_back() {
    if(!_cursor.is_first()) {
        _cursor.back();
    }
}

void PieceTable::row_forward(const size_t step) {
    size_t row = 0, current_col = distance_to_line_start();

    while(row < step && !_cursor.is_last()) {
        _cursor.forward();

        if(is_linebreak(_cursor.index())) {
            ++row;
        }
    }

    size_t line_size = 0;

    while(line_size <= current_col && !_cursor.is_last()) {
        _cursor.forward();

        ++line_size;

        if(is_linebreak(_cursor.index())) {
            break;
        }
    }
}

void PieceTable::row_back(const size_t step) {
    size_t row = 0, line_size = 0, prev_line_size = 0;

    while(row <= step && !_cursor.is_first()) {
        _cursor.back();

        if(is_linebreak(_cursor.index())) {
            ++row;
        }

        if(row == 0) {
            ++line_size;
        } else if(row == 1) {
            ++prev_line_size;
        }
    }

    const auto capped = line_size > prev_line_size? prev_line_size - 1: line_size;

    for(auto i = 0; i < capped; ++i) {
        _cursor.forward();
    }
}

Position PieceTable::position() {

    auto pos = Position { row: 0, col: 0 };
    
    for(auto p = _pieces.begin(); p != _cursor.piece; ++p) {
        for(auto i = p->start; i < p->start + p->size; ++i) {
            if(is_linebreak(i)) {
                ++pos.row;
                pos.col = 0;
            } else {
                ++pos.col;
            }
        }
    }

    for(auto i = _cursor.piece->start; i < _cursor.piece->start + _cursor.offset; ++i) {
        if(is_linebreak(i)) {
            ++pos.row;
            pos.col = 0;
        } else {
            ++pos.col;
        }
    }

    return pos;
}