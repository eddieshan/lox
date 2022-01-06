#pragma once

#include "../utils/geometry.h"
#include "../utils/slice.h"

// Navigation module providing free functions to calculate the next position 
// for a navigation action on a text buffer. 
// The input position parameter is required to be a valid index within the slice.
// Boundary check is not guaranteed, the caller is responsible for passing a valid position value.
namespace text::navigation {

    utils::Position text_cursor(const utils::Slice<uint8_t>& text, const size_t pos);

    namespace col {
        size_t right(const utils::Slice<uint8_t>& text, const size_t pos);
        size_t left(const utils::Slice<uint8_t>& text, const size_t pos);
    }

    namespace row
    {
        size_t down(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step = 1);
        size_t up(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step = 1);
        size_t start(const utils::Slice<uint8_t>& text, const size_t pos);
        size_t end(const utils::Slice<uint8_t>& text, const size_t pos);        
    }
    
}