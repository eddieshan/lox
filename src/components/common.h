#pragma once

#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../buffers/buffer.h"
#include "../syntax/grammar.h"

namespace components {
    struct EditorState {
        buffers::PieceTable text_buffer;
        buffers::Buffer text_area;
        size_t pos;
        buffers::FixedBuffer screen_buffer;
        utils::WindowSize window_size;
    };

    struct Config {
        syntax::Grammar grammar;
    };
}