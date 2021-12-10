#include <charconv>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "line_counter_view.h"

using namespace utils;
using namespace term;
using namespace views;

void line_counter_view::render(const models::TextState& text_state, buffers::FixedBuffer& buffer) {
    std::array<uint8_t, 3> line_count = { 0, 0, 0 };

    buffer.write(ansi::Home);
    buffer.write(ansi::Dim);
    
    for(auto i = 0; i < text_state.n_lines; ++i) {
        std::to_chars((char*)line_count.data(), (char*)line_count.data() + line_count.size(), i + 1);
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