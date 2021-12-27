#include "../utils/convert.h"
#include "../utils/geometry.h"
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

    buffer.esc(start_pos.col, ansi::ColumnRelative);

    while(!tokenizer.is_end()) {
        const auto token = tokenizer.next();

        if(token.type == TokenType::NewLine) {
            buffer.esc(ansi::NextLine);
            buffer.esc(start_pos.col, ansi::ColumnRelative);
        } else {
            const auto style = theme::syntax_style(token.type);
            buffer.esc(style);
            buffer.write(token.span);
            buffer.esc(ansi::ResetForeground);
        }
    }

    return start_pos;
}