#pragma once

#include "../buffers/buffer.h"

namespace models {

    enum class CommandType {
        OpenFile
    };

    struct Command {
        CommandType type;
        buffers::Buffer text;
    };
}