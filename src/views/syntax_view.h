#pragma once

#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"
#include "../syntax/tokenize.h"

namespace views::syntax_view {
    constexpr utils::Position StartPos = utils::Position { row: 0, col: 4 };

    void render(syntax::Tokenizer& tokenizer, const size_t pos, buffers::FixedBuffer& buffer);
}