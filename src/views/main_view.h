#pragma once

#include "../buffers/fixed_buffer.h"
#include "../models/editor_state.h"
#include "../settings/config.h"

namespace views::main_view {
    void render(const models::EditorState& state, const settings::Config& config, buffers::FixedBuffer& screen_buffer);
}