#include "../utils/array.h"
#include "../utils/units.h"
#include "../buffers/fixed_buffer.h"
#include "../term/term.h"
#include "../settings/config.h"
#include "../syntax/grammar.h"
#include "../models/editor_state.h"
#include "../views/main_view.h"
#include "../controllers/controller.h"
#include "../settings/theme.h"

#include "editor.h"

using namespace utils;
using namespace buffers;
using namespace term;
using namespace components;
using namespace controllers;
using namespace views;
using namespace settings;
using namespace models;

void render(EditorState& state, const Config& config, FixedBuffer& screen_buffer) {
    main_view::render(state, config, screen_buffer);
    term::write(screen_buffer.data());
    term::flush();
    screen_buffer.clear();
}

void editor::run() {
    const auto result = term::enable_raw_mode();
    constexpr auto ScreenBufferSize = 16*units::Kb;

    const auto preamble = array::concat(theme::Background, theme::Foreground, ansi::ClearScreen);
    auto screen_buffer = buffers::FixedBuffer(ScreenBufferSize, slice::from(preamble));

    auto wait_for_events = true;
    auto state = editor_state::build();

    const auto config = Config {
        grammar: syntax::build()
    };

    render(state, config, screen_buffer);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            wait_for_events = controller::process(key, state);
            render(state, config, screen_buffer);
        }
    } while(wait_for_events);
}