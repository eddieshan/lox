#pragma once

#include <cstdint>
#include "../utils/array_list.h"

namespace models {

    enum class CommandType {
        OpenFile
    };

    struct Command {
        CommandType type;
        utils::ArrayList<uint8_t> text;
    };
}