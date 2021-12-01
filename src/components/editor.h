#ifndef EDITOR_H
#define EDITOR_H

#include "../term/term.h"
#include "../utils/geometry.h"
#include "../buffers/piece_table.h"
#include "../components/text_view.h"
#include "../components/cursor.h"

namespace components {
    struct EditorState {
        bool is_started;
    };

    class Editor {
        private:
            Editor();

            EditorState _state;
            buffers::PieceTable _text_buffer;
            components::TextView _text_view;
            utils::Position _cursor;

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