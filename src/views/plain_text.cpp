#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../buffers/vt100_buffer.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

Position views::plain_text(const Slice<uint8_t>& text, buffers::Vt100Buffer& buffer) {

    constexpr utils::Position start_pos = utils::Position { row: 0, col: 4 };

    buffer.esc(start_pos.col, ansi::ColumnRelative);

    size_t last_cr = 0, last = text.size - 1;

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;

        if(is_line_break || (i == last)) {
            const auto line_size = is_line_break? i - last_cr : i - last_cr + 1;
            buffer.write(text.data + last_cr, line_size);

            if(is_line_break) {
                buffer.esc(ansi::NextLine);
                buffer.esc(start_pos.col, ansi::ColumnRelative);
                last_cr = i + 1;
            }
        }
    }

    return start_pos;
}