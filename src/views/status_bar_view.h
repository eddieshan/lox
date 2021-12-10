#ifndef STATUS_BAR_VIEW_H
#define STATUS_BAR_VIEW_H

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"

namespace views::status_bar_view {
    void render(const utils::Position& pos, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);
}

#endif