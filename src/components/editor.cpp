#include "../utils/array.h"
#include "../utils/units.h"
#include "../buffers/buffer.h"
#include "../term/term.h"
#include "../settings/config.h"
#include "../syntax/grammar.h"
#include "../models/editor_state.h"
#include "../views/views.h"
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

void render(const Editor& editor, Buffer& screen_buffer, View view) {
    term::write(editor.config.preamble);
    view(editor.state, editor.config, screen_buffer);
    term::write(screen_buffer.text());
    term::flush();
    screen_buffer.clear();
}

void editor::run() {
    const auto result = term::enable_raw_mode();
    constexpr auto ScreenBufferSize = 16*units::Kb;

    const auto preamble = array::concat(theme::Background, theme::Foreground, ansi::ClearScreen);
    auto screen_buffer = Buffer(ScreenBufferSize);

    auto wait_for_events = true;

    const auto config = Config {
        grammar: syntax::build(),
        preamble: slice::from(preamble)
    };

    auto controller = controllers::edit;

    auto editor = Editor {
        state: editor_state::build(),
        config: config
    };

    render(editor, screen_buffer, views::edit);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            const auto result = controller(key, editor.state);
            controller = result.controller;
            wait_for_events = !result.exit;

            if(result.text_updated) {
                editor.state.text_area.clear();
                editor.state.text_buffer.accept<Buffer, &Buffer::write>(editor.state.text_area);
            }

            render(editor, screen_buffer, result.view);
        }
    } while(wait_for_events);
}