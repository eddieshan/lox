#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../utils/slice.h"
#include "../utils/array.h"
#include "../term/ansi.h"
#include "../buffers/buffer.h"
#include "views.h"

using namespace views;
using namespace utils;

// The conversion of row and col to char has unknown size at compile time.
// To avoid heap allocations, the converted rows and col are padded to three digits.
// Thus, the VT100 escape to set cursor pos is aligned to a fixed length of 10 bytes.
// This works based on two assumptions,
// - that rows and cols will never be greater than 999 each,
// - empty chars in an VT100 sequence are ignored.
void views::cursor(const Position& screen_pos, buffers::Buffer& buffer) {
    auto pos = term::ansi::CursorMv;
    const auto row_start = pos.data() + 2, col_start = pos.data() + 6;
 
    convert::to_chars_3(screen_pos.row + 1, row_start);
    convert::to_chars_3(screen_pos.col + 1, col_start);

    buffer.write(pos.data(), pos.size());
}