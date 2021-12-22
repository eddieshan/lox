#include "../term/term.h"
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

//using namespace components;
using namespace views;
using namespace text;
using namespace term;

void main_view::render(models::EditorState& state, const settings::Config& config) {
    const auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text, config.grammar);
    syntax_view::render(tokenizer, state.pos, state.screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos);

    status_bar_view::render(text_state, state.window_size, state.screen_buffer);
    command_view::render(state.command, state.window_size, state.screen_buffer);
    line_counter_view::render(text_state, state.screen_buffer);
    cursor::render(text_state.pos + text_view::StartPos, state.screen_buffer);

    term::write(state.screen_buffer.data());
    state.screen_buffer.clear();
    
    term::flush();
}