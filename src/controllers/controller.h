#pragma once

#include "../term/term.h"
#include "../models/editor_state.h"

namespace controllers::controller {
    bool process(const term::Key& key, models::EditorState& state);
}