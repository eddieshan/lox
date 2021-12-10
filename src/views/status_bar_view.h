#ifndef STATUS_BAR_VIEW_H
#define STATUS_BAR_VIEW_H

#include <memory>

#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"
#include "../models/text_area.h"

namespace views::status_bar_view {
    void render(const models::TextState& text_state, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);
}

#endif