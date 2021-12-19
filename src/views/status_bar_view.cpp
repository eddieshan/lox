#include <array>

#include "../utils/convert.h"
#include "../term/ansi.h"
#include "../models/text_area.h"
#include "status_bar_view.h"

using namespace utils;
using namespace term;
using namespace views;

void status_bar_view::render(const models::TextCursor& text_state, const WindowSize& window_size, buffers::FixedBuffer& buffer) {
    constexpr auto caption = array::from<uint8_t>((uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)':', (uint8_t)0, (uint8_t)0, (uint8_t)0);

    convert::to_chars_3(text_state.pos.row + 1, (uint8_t*)caption.data());
    convert::to_chars_3(text_state.pos.col + 1, (uint8_t*)caption.data() + 4);

    constexpr auto cursor_seq = term::ansi::CursorMv;
    const auto row_start = cursor_seq.data() + 2, col_start = cursor_seq.data() + 6;

    convert::to_chars_3(window_size.rows, (uint8_t*)row_start);
    convert::to_chars_3(window_size.cols - caption.size(), (uint8_t*)col_start);

    buffer.write(cursor_seq);
    buffer.write(caption);
}