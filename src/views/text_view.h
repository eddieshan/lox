#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"

namespace views::text_view {

    void render(const utils::Slice<uint8_t>& text, buffers::FixedBuffer& buffer);

    utils::Position cursor(const utils::Slice<uint8_t>& text, const size_t pos);
}

#endif