#include <array>
#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/array.h"
#include "../buffers/fixed_buffer.h"
#include "cursor.h"

using namespace components;
using namespace utils;

// The conversion of row and col to char has unknown size at compile time.
// To avoid heap allocations, the converted rows and col are padded to three digits.
// Thus, the VT100 escape to set cursor pos is aligned to a fixed length of 10 bytes.
// This works based on two assumptions,
// - that rows and cols will never be greater than 999 each,
// - empty chars in an VT100 sequence are ignored.
// TODO: 
//  Returning the escape array by value is not very efficient.
//  Find out if there is a better implementation.
void cursor::render(const Position& screen_pos, buffers::FixedBuffer& buffer) {
    auto pos = utils::array::from<uint8_t>((uint8_t)27, (uint8_t)91, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)59, (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)72); // x1b[row:colH
    const auto row_start = pos.data() + 2, col_start = pos.data() + 6;
 
    std::to_chars((char*)row_start, (char*)row_start + 2, screen_pos.row + 1);
    std::to_chars((char*)col_start, (char*)col_start + 2, screen_pos.col + 1);

    buffer.write(pos);
}