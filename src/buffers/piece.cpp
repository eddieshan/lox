#include <stdio.h>
#include <list>

#include "piece.h"

using namespace buffers;

PieceCursor::PieceCursor(std::list<Piece> &pieces):
    offset(0),
    piece(pieces.begin()),
    _end(pieces.end()) {}

size_t PieceCursor::index() {
    return piece->start + offset;
}

void PieceCursor::back() {
    if(offset == 0) {
        piece = std::prev(piece);
        offset = piece->size - 1;
    } else {
        offset--;
    }    
}

void PieceCursor::forward() {
    if(offset < piece->size - 1) {
        offset++;
    } else {
        piece = std::next(piece);
        offset = 0;
    }
}

bool PieceCursor::is_first() {
    return piece->start == 0 && offset == 0;
}

bool PieceCursor::is_last() {
    return std::next(piece) == _end && (piece->size == 0 || offset == piece->size - 1);
}

bool PieceCursor::end_of_piece() {
    return piece->size == 0 || offset == piece->size - 1;
}