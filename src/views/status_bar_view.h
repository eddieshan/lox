#pragma once

#include "../buffers/fixed_buffer.h"
#include "../models/common.h"

namespace views::status_bar_view {
    void render(const models::TextCursor& text_state, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);
}