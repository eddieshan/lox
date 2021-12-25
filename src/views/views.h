#pragma once

#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../buffers/fixed_buffer.h"
#include "../models/common.h"
#include "../models/editor_state.h"
#include "../settings/config.h"
#include "../syntax/tokenize.h"

namespace views {

    using View = void (*)(const models::EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer);

    void edit(const models::EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer);

    void command_line(const models::EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer);

    utils::Position plain_text(const utils::Slice<uint8_t>& text, const size_t pos, buffers::FixedBuffer& buffer);

    utils::Position syntax(syntax::Tokenizer& tokenizer, const size_t pos, buffers::FixedBuffer& buffer);

    void status_bar(const models::TextCursor& text_state, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);

    void line_counter(const models::TextCursor& text_state, buffers::FixedBuffer& buffer);

    // Writes a VT100 sequence to move the cursor to the desired screen position.
    // The screen position is required to be zero based.
    // VT100 screen coordinates are 1 based so row and col are incremented by 1.
    void cursor(const utils::Position& pos, buffers::FixedBuffer& buffer);

}