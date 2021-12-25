#pragma once

#include "../term/term.h"
#include "../models/editor_state.h"
#include "../views/views.h"

namespace controllers {

    struct ControllerResult;

    using Controller = ControllerResult (*)(const term::Key& key, models::EditorState& state);

    struct ControllerResult {
        Controller controller;
        views::View view;
        bool exit;
        bool text_updated;
    };

    ControllerResult command_line(const term::Key& key, models::EditorState& state);

    ControllerResult edit(const term::Key& key, models::EditorState& state);
}