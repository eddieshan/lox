#pragma once

#include "../models/editor_state.h"
#include "../settings/config.h"

namespace views::main_view {
    void render(models::EditorState& state, const settings::Config& config);
}