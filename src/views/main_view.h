#pragma once

#include <cstdint>

#include "../buffers/fixed_buffer.h"
#include "../models/editor_state.h"
#include "../settings/config.h"

namespace views::main_view {
    void render(const models::EditorState& state, const settings::Config& config, const uint8_t active_views, buffers::FixedBuffer& screen_buffer);
}