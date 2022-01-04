#pragma once

#include <cstddef>
#include <cstdint>

#include "../utils/range.h"
#include "../buffers/piece_table.h"
#include "../buffers/buffer.h"
#include "command.h"

namespace models {

    class EditorState {
        public:
            buffers::PieceTable text_buffer;
            buffers::Buffer text_area;
            size_t pos;
            utils::Range<size_t> visible_region;
            utils::WindowSize window_size;
            models::Command command;

            void update(const size_t new_pos);
    };

    namespace editor_state {
        EditorState build();
    }
}