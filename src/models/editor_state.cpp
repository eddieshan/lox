#include <cstddef>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../utils/array_list.h"
#include "../term/term.h"

#include "command.h"
#include "editor_state.h"

using namespace utils;
using namespace models;
using namespace buffers;
using namespace term;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto TempTextBufferSize = 64*units::Kb;

EditorState editor_state::build() {
    return EditorState {
        text_buffer: PieceTable(TextBufferSize),
        text_area: Buffer(TempTextBufferSize),
        window_size: term::get_window_size(),
        command: models::Command {
            type: models::CommandType::OpenFile,
            text: ArrayList<uint8_t>(1000)
        },
        action_type: ActionType::Edit
    };
}