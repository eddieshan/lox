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

    buffer.esc(start_pos.col, ansi::ColumnRelative);

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;
        if(is_line_break) {
            const auto offset = last_cr == 0? 0 : 1;
            buffer.write(text.data + last_cr + offset, i - last_cr);
            buffer.esc(ansi::NextLine);
            buffer.esc(start_pos.col, ansi::ColumnRelative);
            last_cr = i;
        }
    }

    if (last_cr < text.size) {
        const auto offset = last_cr == 0? 0 : 1;
        buffer.write(text.data + last_cr + offset, text.size - last_cr);
    }

    return start_pos;
}