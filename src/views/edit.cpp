#include <cstdint>

#include "../utils/geometry.h"
#include "../buffers/buffer.h"
#include "../text/navigation.h"
#include "../syntax/tokenize.h"
#include "../models/command.h"
#include "../models/editor_state.h"
#include "../settings/config.h"
#include "views.h"

using namespace views;
using namespace text;
using namespace models;
using namespace utils;

void views::edit(const EditorState& state, const settings::Config& config, buffers::Buffer& screen_buffer) {
    const auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text, config.grammar);
    const auto start_pos = views::syntax(tokenizer, state.pos, screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, state.pos);

    views::status_bar(text_state, state.window_size, screen_buffer);
    views::line_counter(text_state, screen_buffer);
    views::cursor(text_state.pos + start_pos, screen_buffer);
}