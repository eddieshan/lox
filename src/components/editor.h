#pragma once

#include "../models/editor_state.h"
#include "../settings/config.h"

namespace components {

    struct Editor {
        models::EditorState state;
        settings::Config config;
    };

    namespace editor {
        void run();
    }
}