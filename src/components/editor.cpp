#include <stdio.h>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../term/term.h"
#include "../settings/theme.h"
#include "../buffers/piece_table.h"
#include "../models/text_area.h"
#include "../syntax/tokenize.h"
#include "../syntax/grammar.h"
#include "common.h"
#include "controller.h"
#include "view.h"
#include "editor.h"

using namespace utils;
using namespace term;
using namespace buffers;
using namespace models;
using namespace components;
using namespace settings;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto ScreenBufferSize = units::Kb;
constexpr auto TempTextBufferSize = units::Kb;

void editor::run() {
    const auto result = term::enable_raw_mode();
    const auto preamble = array::concat(theme::Background, theme::Foreground, ansi::ClearScreen);

    auto wait_for_events = true;

    auto state = EditorState {
        text_buffer: PieceTable(TextBufferSize),
        text_area: TextArea(TempTextBufferSize),
        screen_buffer: FixedBuffer(ScreenBufferSize, slice::from(preamble)),
        window_size: term::get_window_size()
    };

    const auto config = Config {
        grammar: syntax::build()
    };

    view::render(state, config);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            wait_for_events = controller::process(key, state);
            view::render(state, config);
        }
    } while(wait_for_events);
}