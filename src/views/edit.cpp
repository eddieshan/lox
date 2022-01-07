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
    const auto window_size = state.window_size();
    const auto visible_region = state.visible_region();
    const auto page_size = window_size.rows;

    const auto full_text = state.text();
    const auto clipped_text = slice::sub(full_text, visible_region);
    const auto start_pos = views::syntax(clipped_text, config.grammar, screen_buffer);
    //const auto start_pos = views::plain_text(clipped_text, screen_buffer);

    const auto start_line = slice::count(full_text, ascii::Lf, 0, visible_region.start);
    const auto end_line = slice::count(clipped_text, ascii::Lf) + start_line;
    const auto lines_range = Range<size_t> { start: start_line, end: end_line };

    const auto relative_cursor = navigation::text_cursor(clipped_text, state.pos() - visible_region.start);
    const auto cursor = Position { row: relative_cursor.row + (uint32_t)start_line, col: relative_cursor.col };

    views::status_bar(cursor, window_size, screen_buffer);
    views::line_counter(cursor, lines_range, screen_buffer);

    screen_buffer.esc(relative_cursor + start_pos + Position { row: 1, col: 1 });
}