#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../settings/theme.h"
#include "../term/ansi.h"
#include "../models/text_area.h"
#include "../syntax/tokenize.h"

#include "syntax_view.h"

using namespace utils;
using namespace settings;
using namespace term;
using namespace views;
using namespace models;
using namespace syntax;

TextState syntax_view::render(const Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer) {
    size_t last_output = 0, lines = 1;
    auto screen_pos = Position { row: 0, col: 0 };

    auto move_to_start_col = ansi::escape("\0\0\0C");
    convert::to_chars_3(syntax_view::StartPos.col, (uint8_t*)move_to_start_col.data() + 2);

    auto next_line = array::concat(ansi::NextLine, move_to_start_col);

    buffer.write(move_to_start_col);

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::CarriageReturn;
        if(is_line_break) {
            const auto offset = last_output == 0? 0 : 1;
            buffer.write(text.data + last_output + offset, i - last_output);
            buffer.write(next_line);
            last_output = i;
            ++lines;
        } else if(syntax::is_delimiter(text.data[i])) {
            const auto offset = last_output == 0? last_output : last_output + 1;
            const auto token_type = syntax::token_type(Slice(text.data + offset, i - offset));

            if(token_type == TokenType::Keyword) {
                buffer.write(theme::Keyword);
            } else if(token_type == TokenType::TypeKeyword) {
                buffer.write(theme::TypeKeyword);
            } else {
                buffer.write(theme::Plain);
            }

            buffer.write(text.data + offset, i - offset + 1);
            buffer.write(ansi::ResetForeground);
            
            last_output = i;
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

    if (last_output < text.size) {
        const auto offset = last_output == 0? 0 : 1;
        buffer.write(text.data + last_output + offset, text.size - last_output);
    }

    return TextState { pos: screen_pos, n_lines: lines };
}