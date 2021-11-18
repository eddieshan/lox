#include <stdio.h>

#include "editor.h"
#include "term.h"
#include "keys.h"
#include "ansi.h"
#include "cursor.h"

Editor::Editor(): _cursor(term::get_window_size()) {

}

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
            }
    };

    _screen_buffer.write(term::ansi::Clear);
    _screen_buffer.write(term::ansi::Home);

    _text_buffer.accept<FixedBuffer>(&FixedBuffer::write, _screen_buffer);

    const auto screen_pos = _cursor.screen_pos();
    const auto pos = term::ansi::go_to(screen_pos);
    _screen_buffer.write(pos);

    _screen_buffer.accept(term::write_bytes);

    term::flush();
    _screen_buffer.clear();

    return true;
}

void Editor::clear_screen() {
    _screen_buffer.write(term::ansi::Clear);
    _screen_buffer.write(term::ansi::Home);
    _screen_buffer.accept(term::write_bytes);
    _screen_buffer.clear();
    term::flush();
}

void Editor::start() {
    if(!_state.is_started) {
        const auto result = term::enable_raw_mode();
        const auto window_size = term::get_window_size();

        auto wait_for_events = true;

        clear_screen();

        do {
            const auto key = term::read_key();

            if(key.size > 0) {
                wait_for_events = process(key);
            }
        } while(wait_for_events);
    }
}