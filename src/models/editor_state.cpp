#include "../utils/units.h"
#include "../buffers/piece_table.h"
#include "../buffers/buffer.h"
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
constexpr auto CommandLineSize = 1000;

EditorState editor_state::build() {
    return EditorState {
        text_buffer: PieceTable(TextBufferSize),
        text_area: Buffer(TempTextBufferSize),
        window_size: term::get_window_size(),
        command: Command {
            type: CommandType::OpenFile,
            text: ArrayList<uint8_t>(CommandLineSize)
        }
    };
}