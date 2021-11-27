#include <stdio.h>

#include "../term/term.h"
#include "../utils/ascii.h"
#include "../term/ansi.h"
#include "../utils/array.h"
#include "../buffers/piece_table.h"
#include "../buffers/fixed_buffer.h"
#include "editor.h"
#include "cursor.h"

using namespace utils;
using namespace term;
using namespace buffers;
using namespace components;

Editor::Editor(): 
    _cursor({ row: 0, col : 0 }),
    _screen_buffer(utils::slice::from(term::ansi::Reset)) {}

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
            _text_buffer.row_back();
            break;                    
        case ascii::Down:
            _text_buffer.row_forward();
            break;
        case ascii::Right:
            _text_buffer.col_forward();
            break;
        case ascii::Left:
            _text_buffer.col_back();
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
                _text_buffer.insert(key.code);
            }
    };

    _text_buffer.accept<FixedBuffer>(&FixedBuffer::write, _screen_buffer);
    auto cursor = _text_buffer.position();
    cursor.row++;
    cursor.col++;
    _screen_buffer.write(ansi::go_to(cursor));

    //printf("(%d, %d)", _cursor.row, _cursor.col);

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