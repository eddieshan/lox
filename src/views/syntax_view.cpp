#include "../utils/convert.h"
#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../settings/theme.h"
#include "../term/ansi.h"
#include "../term/term.h"
#include "../syntax/tokenize.h"

#include "syntax_view.h"

using namespace utils;
using namespace settings;
using namespace term;
using namespace views;
using namespace syntax;

void syntax_view::render(Tokenizer& tokenizer, const size_t pos, buffers::FixedBuffer& buffer) {

    auto move_to_start_col = ansi::escape("\0\0\0C");
    convert::to_chars_3(syntax_view::StartPos.col, (uint8_t*)move_to_start_col.data() + 2);

    auto next_line = array::concat(ansi::NextLine, move_to_start_col);

    buffer.write(move_to_start_col);

    while(!tokenizer.is_end()) {
        const auto token = tokenizer.next();

        if(token.type == TokenType::NewLine) {
            buffer.write(next_line);
        } else {
            if(token.type == TokenType::Keyword) {
                buffer.write(theme::Keyword);
            } else if(token.type == TokenType::TypeKeyword) {
                buffer.write(theme::TypeKeyword);
            } else {
                buffer.write(theme::Plain);
            }

            buffer.write(token.span);
            buffer.write(ansi::ResetForeground);
        }
    }
}