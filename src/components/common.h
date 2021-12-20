#pragma once

#include "../utils/geometry.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"
#include "../syntax/grammar.h"

namespace components {
    struct EditorState {
        buffers::PieceTable text_buffer;
        models::TextArea text_area;
        buffers::FixedBuffer screen_buffer;
        utils::WindowSize window_size;
    };

    struct Config {
        syntax::Grammar grammar;
    };
}