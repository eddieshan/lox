#pragma once

#include <cstddef>
#include <cstdint>

#include "../utils/slice.h"
#include "../utils/range.h"
#include "../utils/geometry.h"
#include "../buffers/piece_table.h"
#include "../buffers/vt100_buffer.h"
#include "common.h"
#include "command.h"

namespace models {

    // TODO: EditorState is a god class in the making.
    // A redesign is required asap to break it down.
    // Typical approach would be to introduce a DI container or a service locator.
    // I do not like this option as it seems too heavyweight and would force me
    // to change the replace the current FP-ish design based on free function controllers 
    // and views with a more OOP based design.
    // Needs serious analysis.
    class EditorState {
        private:
            buffers::PieceTable _text_buffer;
            buffers::Vt100Buffer _text_area;
            size_t _pos;
            utils::Range<size_t> _visible_region;
            utils::WindowSize _window_size;

            void update(const size_t new_pos);
            void load_file(const char* path);

        public:
            models::Command command;

            EditorState(const size_t buffer_size, const size_t command_size, const utils::WindowSize& window_size);

            utils::Slice<uint8_t> text() const;
            size_t pos() const;
            utils::WindowSize window_size() const;
            utils::Range<size_t> visible_region() const;

            void move(const Navigator navigate);
            void move(const StepNavigator navigate, const size_t step = 1);
            void insert(const uint8_t val);
            void erase();
            void execute_command();
    };

    namespace editor_state {
        EditorState build();
    }
}