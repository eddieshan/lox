#include "../term/term.h"
#include "../text/navigation.h"
#include "../syntax/tokenize.h"
#include "../views/text_view.h"
#include "../views/syntax_view.h"
#include "../views/status_bar_view.h"
#include "../views/line_counter_view.h"
#include "../views/cursor.h"

#include "common.h"
#include "view.h"

using namespace components;
using namespace views;
using namespace text;
using namespace term;

void view::render(EditorState& state, const Config& config) {
    const auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text, config.grammar);
    syntax_view::render(tokenizer, state.pos, state.screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos);

    status_bar_view::render(text_state, state.window_size, state.screen_buffer);
    line_counter_view::render(text_state, state.screen_buffer);
    cursor::render(text_state.pos + text_view::StartPos, state.screen_buffer);

    term::write(state.screen_buffer.data());
    state.screen_buffer.clear();
    
    term::flush();
}