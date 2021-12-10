#include <charconv>
#include <array>

#include "../utils/geometry.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"

#include "status_bar_view.h"

using namespace utils;
using namespace term;
using namespace views;

void status_bar_view::render(const Position& pos, const WindowSize& window_size, buffers::FixedBuffer& buffer) {
    constexpr auto caption = array::from<uint8_t>((uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)':', (uint8_t)0, (uint8_t)0, (uint8_t)0);
    std::to_chars((char*)caption.data(), (char*)caption.data() + 3, pos.row + 1);
    std::to_chars((char*)caption.data() + 4, (char*)caption.data() + 6, pos.col + 1);

    constexpr auto cursor_seq = term::ansi::CursorMv;
    const auto row_start = cursor_seq.data() + 2, col_start = cursor_seq.data() + 6;
 
    std::to_chars((char*)row_start, (char*)row_start + 3, window_size.rows);
    std::to_chars((char*)col_start, (char*)col_start + 3, window_size.cols - caption.size());

    buffer.write(cursor_seq);
    buffer.write(caption);
}