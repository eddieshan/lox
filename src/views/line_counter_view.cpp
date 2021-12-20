#include "../utils/convert.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "line_counter_view.h"

using namespace utils;
using namespace term;
using namespace views;

void line_counter_view::render(const models::TextCursor& text_state, buffers::FixedBuffer& buffer) {
    std::array<uint8_t, 3> line_count = { (uint8_t)' ', (uint8_t)' ', (uint8_t)' ' };

    buffer.write(ansi::Home);
    buffer.write(ansi::Dim);
    
    for(auto i = 0; i < text_state.n_lines; ++i) {
        convert::to_chars_3(i + 1, line_count.data());
        if(i == text_state.pos.row) {
            buffer.write(ansi::ResetDim);
            buffer.write(line_count);
            buffer.write(ansi::Dim);
        } else {
            buffer.write(line_count);
        }

        buffer.write(ansi::NextLine);
    }

    buffer.write(ansi::ResetDim);
}