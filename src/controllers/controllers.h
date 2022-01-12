#pragma once

#include "../term/term.h"
#include "../models/editor_state.h"
#include "../views/views.h"

namespace controllers {

    struct ActionResult;

    using Controller = ActionResult (*)(const term::Key& key, models::EditorState& state);

    struct ActionResult {
        Controller controller;
        views::View view;
        bool exit;
    };

    ActionResult command_line(const term::Key& key, models::EditorState& state);

    ActionResult edit(const term::Key& key, models::EditorState& state);
}