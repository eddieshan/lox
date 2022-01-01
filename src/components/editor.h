#pragma once

#include "../models/editor_state.h"
#include "../settings/config.h"

namespace components {

    struct Editor {
        models::EditorState state;
        settings::Config config;

        Editor(models::EditorState state_, settings::Config config_):
            state(std::move(state_)),
            config(std::move(config_)) {}

        Editor(Editor&& editor_):
            state(std::move(editor_.state)),
            config(std::move(editor_.config)) {}
    };

    namespace editor {
        void run();
    }
}