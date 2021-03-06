#include <array>

#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../buffers/vt100_buffer.h"
#include "../term/ansi.h"
#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

void views::status_bar(const Position& cursor, const WindowSize& window_size, buffers::Vt100Buffer& buffer) {
    auto caption = std::array { (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)':', (uint8_t)0, (uint8_t)0, (uint8_t)0 };

    convert::to_chars_3(cursor.row + 1, (uint8_t*)caption.data());
    convert::to_chars_3(cursor.col + 1, (uint8_t*)caption.data() + 4);

    buffer.esc(Position { row: window_size.rows, col: window_size.cols - (uint32_t)caption.size() });
    buffer.write(caption.data(), caption.size());
}