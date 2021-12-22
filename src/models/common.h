#pragma once

#include <cstddef>

#include "../utils/geometry.h"

namespace models {
    struct TextCursor {
        utils::Position pos;
        size_t n_lines;
    };
}