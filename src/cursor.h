#ifndef CURSOR_H
#define CURSOR_H

#include "term.h"

class Cursor {
    private:
        const term::WindowSize _window_size;
        unsigned int _pos;

    public:
        Cursor(const term::WindowSize window_size);

        unsigned int pos();

        term::ScreenPosition screen_pos();
        
        void left();
        void right();
        void up();
        void down();
};


#endif
