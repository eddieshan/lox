#ifndef EDITOR_H
#define EDITOR_H

#include "term.h"
#include "piece_table.h"
#include "fixed_buffer.h"
#include "cursor.h"

struct EditorState {
    bool is_started;
};

class Editor {
    private:
        Editor();

        EditorState _state;
        PieceTable _text_buffer;
        FixedBuffer _screen_buffer;
        Cursor _cursor;

        bool process(const term::Key& key);
        void flush();

    public:
        static Editor& instance();
        void start();

        Editor(Editor const&) = delete;
        void operator =(Editor const&) = delete;
};

#endif