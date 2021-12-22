#include "../utils/array.h"
#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../term/ansi.h"
#include "command_view.h"

using namespace utils;
using namespace term;
using namespace views;

void command_view::render(const models::Command& command, const WindowSize& window_size, buffers::FixedBuffer& buffer) {
    constexpr auto cursor_seq = term::ansi::CursorMv;
    const auto row_start = cursor_seq.data() + 2, col_start = cursor_seq.data() + 6;

    convert::to_chars_3(window_size.rows, (uint8_t*)row_start);
    convert::to_chars_3(0, (uint8_t*)col_start);

    buffer.write(cursor_seq);
    buffer.write(command.text.text());
}