#ifndef CURSOR_H
#define CURSOR_H

#include "../utils/geometry.h"

namespace components {
    class Cursor {
        private:
            const utils::WindowSize _window_size;
            unsigned int _pos;

        public:
            Cursor(const utils::WindowSize window_size);

            unsigned int pos();

            utils::Position screen_pos();
            
            void left();
            void right();
            void up();
            void down();
    };
}

#endif
