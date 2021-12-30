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

Position views::syntax(const Slice<uint8_t>& text, const Grammar& grammar, buffers::Buffer& buffer) {

    constexpr Position start_pos = utils::Position { row: 0, col: 4 };

    buffer.esc(start_pos.col, ansi::ColumnRelative);

    size_t last_cr = 0, last = text.size - 1;

    for(auto i = 0; i < text.size; ++i) {
        const auto is_line_break = text.data[i] == ascii::Lf;
        const auto is_last = i == last;

        if(is_line_break || is_last) {
            const auto line_size = is_line_break? i - last_cr : i - last_cr + 1;
            const auto line = Slice(text.data + last_cr, line_size);

            auto tokenizer = Tokenizer(line, grammar);

            while(!tokenizer.is_end()) {
                const auto token = tokenizer.next();
                const auto style = theme::syntax_style(token.type);
                buffer.esc(style);
                buffer.write(token.span);
                buffer.esc(ansi::ResetForeground);
            }

            if(is_line_break) {
                buffer.esc(ansi::NextLine);
                buffer.esc(start_pos.col, ansi::ColumnRelative);

                last_cr = i + 1;
            }
        }
    }

    return start_pos;
}