#include <stdio.h>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "../term/ansi.h"
#include "../settings/theme.h"
#include "../buffers/piece_table.h"
#include "../text/navigation.h"
#include "../models/text_area.h"
#include "../views/text_view.h"
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

const auto preamble = array::concat(
    ansi::ClearScreen,
    theme::Background,
    theme::Foreground
);

Editor::Editor():
    _cursor({ row: 0, col : 0 }),
    _text_area(TextArea(TempTextBufferSize)),
    _screen_buffer(FixedBuffer(ScreenBufferSize, slice::from(preamble))),
    _text_buffer(TextBufferSize) {}

Editor& Editor::instance()
{
    static Editor instance;
    return instance;
}

bool Editor::process(const term::Key& key) {

    switch (key.code) {
        case ascii::CtrlQ:
            return false;
            break;
        case ascii::Cr:
            break;
        case ascii::Up:
            _text_area.move_to(navigation::row_back);
            break;
        case ascii::Down:
            _text_area.move_to(navigation::row_forward);
            break;
        case ascii::Right:
            _text_area.move_to(navigation::col_forward);
            break;
        case ascii::Left:
            _text_area.move_to(navigation::col_back);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            break;
        case ascii::LnEnd:
            break;
        case ascii::Del:
            break;
        case ascii::BSpace:
            break;
        default:
            if (key.size == 1) {
                const auto next_pos = _text_buffer.insert(key.code, _text_area.position());
                _text_area.clear();
                _text_buffer.accept(&TextArea::write, _text_area);
                _text_area.move_to(next_pos);
            }
    };

    render();

    return true;
}

void Editor::render() {
    const auto screen_pos = text_view::render(_text_area.text(), _text_area.position(), _screen_buffer);
    cursor::render(screen_pos, _screen_buffer);

    _screen_buffer.accept(term::write);
    _screen_buffer.clear();
    
    term::flush();
}

void Editor::start() {
    if(!_state.is_started) {
        const auto result = term::enable_raw_mode();
        const auto window_size = term::get_window_size();

        auto wait_for_events = true;

        render();

        do {
            const auto key = term::read_key();

            if(key.size > 0) {
                wait_for_events = process(key);
            }
        } while(wait_for_events);
    }
}