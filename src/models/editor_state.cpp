#include <cstddef>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../settings/theme.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "../buffers/buffer.h"
#include "../term/term.h"

#include "command.h"
#include "editor_state.h"

using namespace utils;
using namespace models;
using namespace buffers;
using namespace settings;
using namespace term;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto ScreenBufferSize = 16*units::Kb;
constexpr auto TempTextBufferSize = 64*units::Kb;

EditorState editor_state::build() {
    const auto preamble = array::concat(theme::Background, theme::Foreground, ansi::ClearScreen);

    return EditorState {
        text_buffer: PieceTable(TextBufferSize),
        text_area: Buffer(TempTextBufferSize),
        screen_buffer: FixedBuffer(ScreenBufferSize, slice::from(preamble)),
        window_size: term::get_window_size(),
        command: models::Command {
            type: models::CommandType::OpenFile,
            text: Buffer(1000)
        },
        action_type: ActionType::Edit
    };
}