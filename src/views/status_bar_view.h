#pragma once

#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"

namespace views::status_bar_view {
    void render(const models::TextState& text_state, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);
}