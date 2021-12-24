#pragma once

#include "../term/term.h"
#include "../models/editor_state.h"

namespace controllers {

    struct ControllerResult;

    using Controller =  ControllerResult (*)(const term::Key& key, models::EditorState& state);

    struct ControllerResult {
        Controller controller;
        bool exit;
        bool text_updated;
        uint8_t active_views;
    };
}