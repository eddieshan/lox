#include "../utils/array.h"
#include "../utils/geometry.h"
#include "../utils/convert.h"
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
    constexpr auto Open = array::to_uint8_t(" Open: ");
}

Position render(const models::Command& command, const WindowSize& window_size, buffers::FixedBuffer& buffer) {
    constexpr auto cursor_seq = term::ansi::CursorMv;
    const auto row_start = cursor_seq.data() + 2, col_start = cursor_seq.data() + 6;

    convert::to_chars_3(window_size.rows, (uint8_t*)row_start);
    convert::to_chars_3(0, (uint8_t*)col_start);

    buffer.write(theme::Command);
    buffer.write(cursor_seq);
    buffer.write(term::ansi::ClearLine);
    buffer.write(messages::Open);
    buffer.write(command.text.data());

    return Position { row: window_size.rows, col: messages::Open.size() };
}

void views::command_line(const EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer) {
    const auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text, config.grammar);
    views::syntax(tokenizer, state.pos, screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos);

    views::status_bar(text_state, state.window_size, screen_buffer);
    views::line_counter(text_state, screen_buffer);

    const auto pos = render(state.command, state.window_size, screen_buffer);
    views::cursor(Position { row: 0, col: (uint32_t) state.pos } + pos, screen_buffer);
}