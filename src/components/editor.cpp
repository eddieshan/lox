#include <stdio.h>

#include "../utils/units.h"
#include "../utils/array.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "../term/ansi.h"
#include "../buffers/piece_table.h"
#include "text_view.h"
#include "editor.h"
#include "cursor.h"
using namespace utils;
using namespace term;
using namespace buffers;
using namespace components;

Editor::Editor(): 
    _cursor({ row: 0, col : 0 }),
    _text_view(TextView(units::Kb)) {}

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
            _text_view.row_back();
            break;                    
        case ascii::Down:
            _text_view.row_forward();
            break;
        case ascii::Right:
            _text_view.col_forward();
            break;
        case ascii::Left:
            _text_view.col_back();
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
                const auto next_pos = _text_buffer.insert(key.code, _text_view.position());
                _text_view.clear();
                _text_buffer.accept(&TextView::write, _text_view);
                _text_view.move_to(next_pos);
            }
    };

    render();

    return true;
}

void Editor::render() {

    term::write_bytes(slice::from(term::ansi::Reset));

    _text_view.render(term::write_bytes);

    auto screen_pos = _text_view.screen_position();

    cursor::render(screen_pos, term::write_bytes);

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