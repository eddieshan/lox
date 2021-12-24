#pragma once

#include "../term/term.h"
#include "../models/editor_state.h"
#include "common.h"

namespace controllers::command_controller {
    ControllerResult process(const term::Key& key, models::EditorState& state);
}