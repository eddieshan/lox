#ifndef LINE_COUNTER_VIEW_H
#define LINE_COUNTER_VIEW_H

#include "../models/text_area.h"
#include "../buffers/fixed_buffer.h"

namespace views::line_counter_view {
    void render(const models::TextState& text_state, buffers::FixedBuffer& buffer);
}

#endif