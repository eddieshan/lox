#include "../utils/array.h"
#include "../utils/units.h"
#include "../buffers/fixed_buffer.h"
#include "../term/term.h"
#include "../settings/config.h"
#include "../syntax/grammar.h"
#include "../models/editor_state.h"
#include "../views/main_view.h"
#include "../controllers/controllers.h"
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

void render(const EditorState& state, const Config& config, FixedBuffer& screen_buffer, uint8_t active_views) {
    main_view::render(state, config, active_views, screen_buffer);
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

    auto controller = controllers::edit;

    render(state, config, screen_buffer, active_views::Edit);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            const auto result = controller(key, state);
            controller = result.controller;
            wait_for_events = !result.exit;

            if(result.text_updated) {
                state.text_area.clear();
                state.text_buffer.accept<Buffer, &Buffer::write>(state.text_area);
            }

            render(state, config, screen_buffer, result.active_views);
        }
    } while(wait_for_events);
}