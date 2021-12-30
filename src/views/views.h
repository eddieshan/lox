#pragma once

#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../buffers/buffer.h"
#include "../models/common.h"
#include "../models/editor_state.h"
#include "../settings/config.h"
#include "../syntax/tokenize.h"

namespace views {

    using View = void (*)(const models::EditorState& state, const settings::Config& config, buffers::Buffer& screen_buffer);

    void edit(const models::EditorState& state, const settings::Config& config, buffers::Buffer& screen_buffer);

    void command_line(const models::EditorState& state, const settings::Config& config, buffers::Buffer& screen_buffer);

    utils::Position plain_text(const utils::Slice<uint8_t>& text, buffers::Buffer& buffer);

    utils::Position syntax(const utils::Slice<uint8_t>& text, const syntax::Grammar& grammar, buffers::Buffer& buffer);

    void status_bar(const models::TextCursor& text_state, const utils::WindowSize& window_size, buffers::Buffer& buffer);

    void line_counter(const models::TextCursor& text_state, buffers::Buffer& buffer);
}