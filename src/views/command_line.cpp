#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../buffers/buffer.h"
#include "../text/navigation.h"
#include "../term/ansi.h"
#include "../settings/theme.h"
#include "../models/editor_state.h"

#include "views.h"

using namespace utils;
using namespace term;
using namespace text;
using namespace models;
using namespace views;
using namespace settings;

namespace messages {
    const auto Open = slice::from(" Open: ");
}

Position render(const Command& command, const WindowSize& window_size, buffers::Buffer& buffer) {
    buffer.esc(theme::command_line::Background);
    buffer.esc(theme::command_line::Foreground);
    buffer.esc(Position { row: window_size.rows, col: 0 });
    buffer.esc(term::ansi::ClearLine);
    buffer.write(messages::Open);
    buffer.write(command.text());

    return Position { row: window_size.rows, col: (uint32_t) messages::Open.size };
}

void views::command_line(const EditorState& state, const settings::Config& config, buffers::Buffer& screen_buffer) {
    const auto text = state.text();
    views::syntax(text, config.grammar, screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos());
    const auto window_size = state.window_size();

    views::status_bar(text_state, window_size, screen_buffer);
    //views::line_counter(text_state, screen_buffer);

    const auto pos = render(state.command, window_size, screen_buffer);
    screen_buffer.esc(Position { row: 0, col: (uint32_t) state.command.pos() } + pos + Position { row: 1, col: 1 });
}