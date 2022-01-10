#pragma once

#include "../utils/range.h"
#include "../utils/slice.h"
#include "../utils/geometry.h"
#include "../buffers/vt100_buffer.h"
#include "../models/editor_state.h"
#include "../settings/config.h"
#include "../syntax/tokenize.h"

namespace views {

    using View = void (*)(const models::EditorState& state, const settings::Config& config, buffers::Vt100Buffer& screen_buffer);

    void edit(const models::EditorState& state, const settings::Config& config, buffers::Vt100Buffer& screen_buffer);

    void command_line(const models::EditorState& state, const settings::Config& config, buffers::Vt100Buffer& screen_buffer);

    utils::Position plain_text(const utils::Slice<uint8_t>& text, buffers::Vt100Buffer& buffer);

    utils::Position syntax(const utils::Slice<uint8_t>& text, const syntax::Grammar& grammar, buffers::Vt100Buffer& buffer);

    void status_bar(const utils::Position& cursor, const utils::WindowSize& window_size, buffers::Vt100Buffer& buffer);

    void line_counter(const utils::Position& cursor, const utils::Range<size_t>& range, buffers::Vt100Buffer& buffer);
}