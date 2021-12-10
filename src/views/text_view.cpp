#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "text_view.h"

using namespace utils;
using namespace term;
using namespace views;

Position text_view::render(const Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer) {
    size_t last_cr = 0, lines = 1;
    auto screen_pos = Position { row: 0, col: 0};

    constexpr auto move_to_start_col = ansi::escape(array::from<char>('3', 'C'));
    constexpr auto next_line = array::concat(ansi::NextLine, move_to_start_col);

    buffer.write(move_to_start_col);

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::CarriageReturn;
        if(is_line_break) {
            const auto offset = last_cr == 0? 0 : 1;
            buffer.write(text.data + last_cr + offset, i - last_cr);
            buffer.write(next_line);
            last_cr = i;
            ++lines;
        }

        if(i < pos) {
            if(is_line_break) {
                ++screen_pos.row;
                screen_pos.col = 0;

            } else {
                ++screen_pos.col;
            }
        }
    }

    if (last_cr < text.size) {
        const auto offset = last_cr == 0? 0 : 1;
        buffer.write(text.data + last_cr + offset, text.size - last_cr);
    }

    std::array<uint8_t, 3> line_count = { 0, 0, 0 };

    buffer.write(ansi::Home);
    buffer.write(ansi::Dim);
    
    for(auto i = 0; i < lines; ++i) {
        std::to_chars((char*)line_count.data(), (char*)line_count.data() + line_count.size(), i + 1);
        if(i == screen_pos.row) {
            buffer.write(ansi::ResetDim);
            buffer.write(line_count);
            buffer.write(ansi::Dim);
        } else {
            buffer.write(line_count);
        }

        buffer.write(ansi::NextLine);
    }

    buffer.write(ansi::ResetDim);

    return screen_pos;
}