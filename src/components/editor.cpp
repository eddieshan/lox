#include <stdio.h>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../term/term.h"
#include "../term/ansi.h"
#include "../settings/theme.h"
#include "../buffers/piece_table.h"
#include "../text/navigation.h"
#include "../models/text_area.h"
#include "../syntax/tokenize.h"
#include "../views/text_view.h"
#include "../views/syntax_view.h"
#include "../views/status_bar_view.h"
#include "../views/line_counter_view.h"
#include "../views/cursor.h"
#include "editor.h"

using namespace utils;
using namespace term;
using namespace buffers;
using namespace text;
using namespace models;
using namespace views;
using namespace components;
using namespace settings;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto ScreenBufferSize = units::Kb;
constexpr auto TempTextBufferSize = units::Kb;

void render(EditorState& state) {
    auto text = state.text_area.text();
    auto tokenizer = syntax::Tokenizer(text);
    const auto text_pos = state.text_area.position();
    syntax_view::render(tokenizer, text_pos, state.screen_buffer);
 
    const auto text_state = navigation::text_cursor(text, text_pos);

    status_bar_view::render(text_state, state.window_size, state.screen_buffer);
    line_counter_view::render(text_state, state.screen_buffer);
    cursor::render(text_state.pos + text_view::StartPos, state.screen_buffer);

    term::write(state.screen_buffer.data());
    state.screen_buffer.clear();
    
    term::flush();
}

bool process(const term::Key& key, EditorState& state) {

    switch (key.code) {
        case ascii::CtrlQ:
            return false;
            break;
        case ascii::Cr:
            break;
        case ascii::Up:
            state.text_area.move_to<navigation::row_back>();
            break;
        case ascii::Down:
            state.text_area.move_to<navigation::row_forward>();
            break;
        case ascii::Right:
            state.text_area.move_to<navigation::col_forward>();
            break;
        case ascii::Left:
            state.text_area.move_to<navigation::col_back>();
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.text_area.move_to<navigation::row_start>();
            break;
        case ascii::LnEnd:
            state.text_area.move_to<navigation::row_end>();
            break;
        case ascii::Del:
            state.text_buffer.erase(state.text_area.position());        
            state.text_area.clear();
            state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);
            break;
        case ascii::BSpace:
            state.text_area.move_to<navigation::col_back>();
            state.text_buffer.erase(state.text_area.position());
            state.text_area.clear();
            state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);        
            break;
        default:
            if (key.size == 1) {
                const auto next_pos = state.text_buffer.insert(key.code, state.text_area.position());
                state.text_area.clear();
                state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);
                state.text_area.move_to(next_pos);
            }
    };

    render(state);

    return true;
}

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

    render(state);

    do {
        const auto key = term::read_key();

        if(key.size > 0) {
            wait_for_events = process(key, state);
        }
    } while(wait_for_events);
}