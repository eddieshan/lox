#include "../utils/convert.h"
#include "../buffers/buffer.h"
#include "../term/ansi.h"
#include "../models/common.h"
#include "../text/navigation.h"

#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

void views::line_counter(const models::TextCursor& text_state, buffers::Buffer& buffer) {
    std::array<uint8_t, 3> line_count = { (uint8_t)' ', (uint8_t)' ', (uint8_t)' ' };

    buffer.write(ansi::Home.data(), ansi::Home.size());
    buffer.write(ansi::Dim.data(), ansi::Dim.size());
    
    for(auto i = 0; i < text_state.n_lines; ++i) {
        convert::to_chars_3(i + 1, line_count.data());
        if(i == text_state.pos.row) {
            buffer.write(ansi::ResetDim.data(), ansi::ResetDim.size());
            buffer.write(line_count.data(), line_count.size());
            buffer.write(ansi::Dim.data(), ansi::Dim.size());
        } else {
            buffer.write(line_count.data(), line_count.size());
        }

        buffer.write(ansi::NextLine.data(), ansi::NextLine.size());
    }

    buffer.write(ansi::ResetDim.data(), ansi::ResetDim.size());
}