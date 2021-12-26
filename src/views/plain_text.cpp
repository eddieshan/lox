#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../buffers/buffer.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

Position views::plain_text(const Slice<uint8_t>& text, const size_t pos, buffers::Buffer& buffer) {

    constexpr utils::Position start_pos = utils::Position { row: 0, col: 4 };

    size_t last_cr = 0;

    auto move_to_start_col = ansi::escape(array::from<char>('\0', '\0', '\0', 'C'));
    convert::to_chars_3(start_pos.col, (uint8_t*)move_to_start_col.data() + 2);

    auto next_line = array::concat(ansi::NextLine, move_to_start_col);

    buffer.write(move_to_start_col.data(), move_to_start_col.size());

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;
        if(is_line_break) {
            const auto offset = last_cr == 0? 0 : 1;
            buffer.write(text.data + last_cr + offset, i - last_cr);
            buffer.write(next_line.data(), next_line.size());
            last_cr = i;
        }
    }

    if (last_cr < text.size) {
        const auto offset = last_cr == 0? 0 : 1;
        buffer.write(text.data + last_cr + offset, text.size - last_cr);
    }

    return start_pos;
}