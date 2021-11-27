#include <stdio.h>
#include <list>

#include "piece.h"

using namespace buffers;

PieceCursor::PieceCursor(std::list<Piece> &pieces):
    offset(0),
    piece(pieces.begin()),
    end(pieces.end()) {}

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

void PieceCursor::forward(const size_t size) {
    if(offset < piece->size - 1 || (index() == size - 1)) {
        offset++;
    } else {
        piece = std::next(piece);
        offset = 0;
    }
}

bool PieceCursor::is_first() {
    return piece->start == 0 && offset == 0;
}

bool PieceCursor::is_last(const size_t size) {
    //printf("Current: (%d, %d, %d)", piece->start, offset, piece);
    const auto is_last_piece = std::next(piece) == end;
    if(is_last_piece) {
        return index() == size - 1? false : offset >= piece->size - 1;
    }

    return false;
}

bool PieceCursor::is_at_end(const size_t size) {
    return size == piece->start + offset;
}