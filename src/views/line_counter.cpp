#include "../utils/range.h"
#include "../utils/geometry.h"
#include "../utils/convert.h"
#include "../buffers/buffer.h"
#include "../term/ansi.h"
#include "../text/navigation.h"

#include "views.h"

using namespace utils;
using namespace term;
using namespace views;

void views::line_counter(const Position& pos, const Range<size_t>& range, buffers::Buffer& buffer) {
    std::array<uint8_t, 3> line_count = { (uint8_t)' ', (uint8_t)' ', (uint8_t)' ' };

    buffer.esc(ansi::Home);
    buffer.esc(ansi::Dim);
    
    for(auto i = range.start; i < range.end; ++i) {
        convert::to_chars_3(i + 1, line_count.data());
        if(i == pos.row) {
            buffer.esc(ansi::ResetDim);
            buffer.write(line_count.data(), line_count.size());
            buffer.esc(ansi::Dim);
        } else {
            buffer.write(line_count.data(), line_count.size());
        }

        buffer.esc(ansi::NextLine);
    }

    buffer.esc(ansi::ResetDim);
}