#include "../utils/geometry.h"
#include "../buffers/fixed_buffer.h"
#include "../text/navigation.h"
#include "../syntax/tokenize.h"
#include "../models/command.h"
#include "../models/editor_state.h"
#include "../settings/config.h"
#include "text_view.h"
#include "syntax_view.h"
#include "command_view.h"
#include "status_bar_view.h"
#include "line_counter_view.h"
#include "cursor.h"

#include "main_view.h"

using namespace views;
using namespace text;
using namespace models;
using namespace utils;

void main_view::render(const EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer) {
    const auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text, config.grammar);
    syntax_view::render(tokenizer, state.pos, screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos);

    status_bar_view::render(text_state, state.window_size, screen_buffer);
    line_counter_view::render(text_state, screen_buffer);

    if(state.action_type == ActionType::Command) {
        const auto pos = command_view::render(state.command, state.window_size, screen_buffer);
        cursor::render(Position { row: 0, col: (uint32_t) state.pos } + pos, screen_buffer);
    } else {
        cursor::render(text_state.pos + text_view::StartPos, screen_buffer);
    }
}