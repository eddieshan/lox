#ifndef EDITOR_H
#define EDITOR_H

#include "../term/term.h"
#include "../utils/geometry.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"

namespace components {
    struct EditorState {
        bool is_started;
    };

    class Editor {
        private:
            Editor();

            EditorState _state;
            buffers::PieceTable _text_buffer;
            models::TextArea _text_area;
            utils::Position _cursor;
            buffers::FixedBuffer _screen_buffer;

            bool process(const term::Key& key);
            void render();

        public:
            static Editor& instance();
            void start();

            Editor(Editor const&) = delete;
            void operator =(Editor const&) = delete;
    };
}

#endif