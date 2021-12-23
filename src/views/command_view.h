#pragma once

#include "../utils/geometry.h"
#include "../buffers/fixed_buffer.h"
#include "../models/command.h"

namespace views::command_view {
    utils::Position render(const models::Command& command, const utils::WindowSize& window_size, buffers::FixedBuffer& buffer);
}