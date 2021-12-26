#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/buffer.h"
#include "../settings/theme.h"
#include "../term/ansi.h"
#include "../term/term.h"
#include "../syntax/tokenize.h"

#include "views.h"

using namespace utils;
using namespace settings;
using namespace term;
using namespace views;
using namespace syntax;

Position views::syntax(Tokenizer& tokenizer, const size_t pos, buffers::Buffer& buffer) {

    constexpr Position start_pos = utils::Position { row: 0, col: 4 };

    auto move_to_start_col = ansi::escape("\0\0\0C");
    convert::to_chars_3(start_pos.col, (uint8_t*)move_to_start_col.data() + 2);

    auto next_line = array::concat(ansi::NextLine, move_to_start_col);

    buffer.write(move_to_start_col.data(), move_to_start_col.size());

    while(!tokenizer.is_end()) {
        const auto token = tokenizer.next();

        if(token.type == TokenType::NewLine) {
            buffer.write(next_line.data(), next_line.size());
        } else {
            const auto style = theme::syntax_style(token.type);
            buffer.write(style.data(), style.size());
            buffer.write(token.span);
            buffer.write(ansi::ResetForeground.data(), ansi::ResetForeground.size());
        }
    }

    return start_pos;
}