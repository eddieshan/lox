#pragma once

#include "../models/text_area.h"
#include "../utils/slice.h"

// Navigation module providing free functions to calculate the next position 
// for a navigation action on a text buffer. 
// The input position parameter is required to be a valid index within the slice.
// Boundary check is not guaranteed, the caller is responsible for passing a valid position value.
namespace text::navigation {

    models::TextCursor text_cursor(const utils::Slice<uint8_t>& text, const size_t pos);

    size_t col_forward(const utils::Slice<uint8_t>& text, const size_t pos);
    size_t col_back(const utils::Slice<uint8_t>& text, const size_t pos);
    size_t row_forward(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step);
    size_t row_back(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step);
    size_t row_start(const utils::Slice<uint8_t>& text, const size_t pos);
    size_t row_end(const utils::Slice<uint8_t>& text, const size_t pos);
}