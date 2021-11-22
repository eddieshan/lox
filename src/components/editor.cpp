#include <stdio.h>

#include "../term/term.h"
#include "../term/keys.h"
#include "../term/ansi.h"
#include "../utils/array.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "editor.h"
#include "cursor.h"

using namespace term;
using namespace buffers;
using namespace components;

Editor::Editor(): 
    _cursor(term::get_window_size()),
    _screen_buffer(utils::slice::from(term::ansi::Reset)) {}

Editor& Editor::instance()
{
    static Editor instance;
    return instance;
}

bool Editor::process(const term::Key& key) {
    switch (key.code) {
        case keys::CtrlQ:
            return false;
            break;
        case keys::Cr:
            break;
        case keys::Up:
            _cursor.up();
            break;                    
        case keys::Down:
            _cursor.down();
            break;
        case keys::Right:            
            _cursor.right();
            break;
        case keys::Left:
            _cursor.left();
            break;
        case keys::Htab:
            break;
        case keys::LnStart:
            break;
        case keys::LnEnd:
            break;
        case keys::Del:
            break;
        case keys::BSpace:
            break;
        default:
            if (key.size == 1) {
                _text_buffer.insert(key.code);
                if(key.code != keys::CarriageReturn) {
                    _cursor.right();
                }
            }
    };

    _text_buffer.accept<FixedBuffer>(&FixedBuffer::write, _screen_buffer);

    flush();

    return true;
}

void Editor::flush() {
    _screen_buffer.accept(term::write_bytes);
    _screen_buffer.clear();
    term::flush();
}

void Editor::start() {
    if(!_state.is_started) {
        const auto result = term::enable_raw_mode();
        const auto window_size = term::get_window_size();

        auto wait_for_events = true;

        flush();

        do {
            const auto key = term::read_key();

            if(key.size > 0) {
                wait_for_events = process(key);
            }
        } while(wait_for_events);
    }
}