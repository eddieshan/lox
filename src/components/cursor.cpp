#include "../utils/geometry.h"
#include "cursor.h"

using namespace components;
using namespace utils;

Cursor::Cursor(const WindowSize window_size):
    _window_size(window_size),
    _pos(1) {}

unsigned int Cursor::pos() {
    return _pos;
}

Position Cursor::screen_pos() {
    return Position {
        row: _pos / _window_size.cols,
        col: _pos % _window_size.cols
    };
}

void Cursor::left() {
    if(_pos > 0) {
        _pos--;
    }
}

void Cursor::right() {
    if(_pos < _window_size.rows *_window_size.cols) {
        _pos++;
    }
}

void Cursor::up() {
    if(_pos >= _window_size.cols) {
        _pos -= _window_size.cols;
    }
}

void Cursor::down() {
    if(_pos <= _window_size.rows *(_window_size.cols - 1)) {
        _pos += _window_size.cols;
    }
}