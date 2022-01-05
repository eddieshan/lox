#include <cstdint>

#include "../utils/geometry.h"
#include "../utils/range.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
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
    const auto page_size = state.window_size.rows;

    const auto full_text = state.text_area.text();
    const auto clipped_text = slice::sub(full_text, state.visible_region);
    //const auto start_pos = views::syntax(text, config.grammar, screen_buffer);
    const auto start_pos = views::plain_text(clipped_text, screen_buffer);
 
    const auto cursor = navigation::text_cursor(full_text, state.pos);

    const auto line_start = slice::count(full_text, ascii::Lf, 0, state.visible_region.start);
    const auto line_end = slice::count(clipped_text, ascii::Lf) + line_start;
    const auto line_range = Range<size_t> { start: line_start, end: line_end };

    views::status_bar(cursor, state.window_size, screen_buffer);
    views::line_counter(cursor, line_range, screen_buffer);

    const auto relative_cursor = Position { row: cursor.row - (uint32_t)line_start, col: cursor.col };

    screen_buffer.esc(relative_cursor + start_pos + Position { row: 1, col: 1 });
}