#include <array>

#include "../utils/convert.h"
#include "../buffers/buffer.h"
#include "../term/ansi.h"
#include "../models/common.h"
#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

void views::status_bar(const models::TextCursor& text_state, const WindowSize& window_size, buffers::Buffer& buffer) {
    constexpr auto caption = array::from<uint8_t>((uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)':', (uint8_t)0, (uint8_t)0, (uint8_t)0);

    convert::to_chars_3(text_state.pos.row + 1, (uint8_t*)caption.data());
    convert::to_chars_3(text_state.pos.col + 1, (uint8_t*)caption.data() + 4);

    constexpr auto cursor_seq = term::ansi::CursorMv;
    const auto row_start = cursor_seq.data() + 2, col_start = cursor_seq.data() + 6;

    convert::to_chars_3(window_size.rows, (uint8_t*)row_start);
    convert::to_chars_3(window_size.cols - caption.size(), (uint8_t*)col_start);

    buffer.write(cursor_seq.data(), cursor_seq.size());
    buffer.write(caption.data(), caption.size());
}