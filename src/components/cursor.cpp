#include "../term/term.h"
#include "cursor.h"

using namespace components;

Cursor::Cursor(const term::WindowSize window_size):
    _window_size(window_size),
    _pos(1) {}

unsigned int Cursor::pos() {
    return _pos;
}

term::ScreenPosition Cursor::screen_pos() {
    return term::ScreenPosition {
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