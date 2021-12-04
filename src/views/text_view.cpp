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
using namespace text;

static constexpr utils::Position StartPos = utils::Position { row: 0, col: 3 };


void text_view::render(const Slice<uint8_t>& text, buffers::FixedBuffer& buffer) {
    size_t last_cr = 0, row = 1;

    constexpr auto move_to_start_col = array::from<uint8_t>((uint8_t)'3', (uint8_t)'C');
    constexpr auto next_line = array::concat(ansi::NextLine, ansi::Csi, move_to_start_col);

    buffer.write(ansi::Csi);
    buffer.write(move_to_start_col);

    for(auto i = 0; i < text.size; ++i) {
        if(text.data[i] == ascii::CarriageReturn) {
            const auto offset = last_cr == 0? 0 : 1;
            buffer.write(text.data + last_cr + offset, i - last_cr);
            last_cr = i;
            ++row;
            buffer.write(next_line);
        }
    }

    if (last_cr < text.size) {
        const auto offset = last_cr == 0? 0 : 1;
        buffer.write(text.data + last_cr + offset, text.size - last_cr);
    }

    std::array<uint8_t, 3> line_count = { 0, 0, 0 };

    buffer.write(ansi::Home);
    
    for(auto i = 1; i <= row; ++i) {
        std::to_chars((char*)line_count.data(), (char*)line_count.data() + line_count.size() - 1, i);
        buffer.write(line_count);
        buffer.write(ansi::NextLine);
    }
}

Position text_view::cursor(const utils::Slice<uint8_t>& text, const size_t pos) {
    return navigation::screen_position(text, pos) + StartPos;
}