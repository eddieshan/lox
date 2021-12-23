#include "../utils/array.h"
#include "../term/term.h"
#include "../settings/config.h"
#include "../syntax/grammar.h"
#include "../models/editor_state.h"
#include "../views/main_view.h"
#include "../controllers/controller.h"

#include "editor.h"

using namespace utils;
using namespace term;
using namespace components;
using namespace controllers;
using namespace views;
using namespace settings;
using namespace models;

void render(EditorState& state, const Config& config) {
    main_view::render(state, config);
    term::write(state.screen_buffer.data());    
    term::flush();
    state.screen_buffer.clear();
}

void editor::run() {
    const auto result = term::enable_raw_mode();

    auto wait_for_events = true;
    auto state = editor_state::build();

    const auto config = Config {
        grammar: syntax::build()
    };

    render(state, config);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            wait_for_events = controller::process(key, state);
            render(state, config);
        }
    } while(wait_for_events);
}