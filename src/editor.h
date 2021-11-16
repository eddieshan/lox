#ifndef EDITOR_H
#define EDITOR_H

#include "term.h"
#include "gap_buffer.h"
#include "fixed_buffer.h"

struct EditorState {
    bool is_started;
};

class Editor {
    private:
        Editor();

        EditorState _state;
        GapBuffer _text_buffer;
        FixedBuffer _screen_buffer;

        bool process(const term::Key& key);

    public:
        static Editor& instance();
        void start();

        Editor(Editor const&) = delete;
        void operator =(Editor const&) = delete;
};

#endif