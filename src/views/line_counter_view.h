#pragma once

#include "../models/text_area.h"
#include "../buffers/fixed_buffer.h"

namespace views::line_counter_view {
    void render(const models::TextCursor& text_state, buffers::FixedBuffer& buffer);
}