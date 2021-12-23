#pragma once

#include <cstddef>

#include "../buffers/piece_table.h"
#include "../buffers/buffer.h"
#include "command.h"

namespace models {
    enum class ActionType {
        Navigate,
        Edit,
        Command
    };

    struct EditorState {
        buffers::PieceTable text_buffer;
        buffers::Buffer text_area;
        size_t pos;
        utils::WindowSize window_size;
        models::Command command;
        ActionType action_type;
    };

    namespace editor_state {
        EditorState build();
    }
}