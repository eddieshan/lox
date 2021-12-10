#ifndef EDITOR_H
#define EDITOR_H

#include "../utils/geometry.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"

namespace components {

    struct EditorState {
        buffers::PieceTable text_buffer;
        models::TextArea text_area;
        buffers::FixedBuffer screen_buffer;
        utils::WindowSize window_size;
    };

    namespace editor {
        void run();
    }
}

#endif