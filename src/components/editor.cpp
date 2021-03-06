#include "../utils/units.h"
#include "../utils/ascii.h"
#include "../buffers/vt100_buffer.h"
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

void render(const Editor& editor, Vt100Buffer& screen_buffer, View view) {
    screen_buffer.clear();
    screen_buffer.esc(theme::Foreground);
    screen_buffer.esc(theme::Background);
    screen_buffer.esc(ansi::Clear);
    screen_buffer.esc(ansi::Home);
    view(editor.state, editor.config, screen_buffer);
    term::write(screen_buffer.text());
    term::flush();
}

void editor::run() {
    const auto result = term::enable_raw_mode();
    constexpr auto ScreenBufferSize = 16*units::Kb;

    auto screen_buffer = Vt100Buffer(ScreenBufferSize);

    auto wait_for_events = true;

    auto controller = controllers::edit;

    auto editor = Editor { state: editor_state::build(), config: Config(syntax::build()) };

    render(editor, screen_buffer, views::edit);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            if(key.code == ascii::CtrlQ) {
                wait_for_events = false;
            } else {
                const auto result = controller(key, editor.state);
                controller = result.controller;
                render(editor, screen_buffer, result.view);
            }
        }
    } while(wait_for_events);
}