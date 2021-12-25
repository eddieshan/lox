#pragma once

#include <cstddef>
#include <cstdint>

#include "../buffers/piece_table.h"
#include "../buffers/buffer.h"
#include "command.h"

namespace models {
    enum class ActionType {
        Navigate,
        Edit,
        Command
    };

    namespace active_views {
        const uint8_t Edit = 1;
        const uint8_t Command = 2;
    }

    struct EditorState {
        buffers::PieceTable text_buffer;
        buffers::Buffer text_area;
        size_t pos;
        utils::WindowSize window_size;
        models::Command command;
    };

    namespace editor_state {
        EditorState build();
    }
}