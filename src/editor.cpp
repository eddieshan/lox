#include <stdio.h>

#include "editor.h"
#include "term.h"
#include "keys.h"
#include "ansi.h"

Editor::Editor() {

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
            break;                    
        case keys::Down:
            break;
        case keys::Right:
            break;
        case keys::Left:
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

    _screen_buffer.write<term::ansi::Clear.size()>(term::ansi::Clear);
    _screen_buffer.write<term::ansi::Home.size()>(term::ansi::Home);

    _text_buffer.accept<FixedBuffer>(&FixedBuffer::write, _screen_buffer);
    _screen_buffer.accept(term::write_bytes);

    term::flush();
    _screen_buffer.clear();

    return true;
}

void Editor::start() {   
    if(!_state.is_started) {
        const auto result = term::enable_raw_mode();
        auto wait_for_events = true;

        do {
            const auto key = term::read_key();

            if(key.size > 0) {
                wait_for_events = process(key);
            }
        }  while(wait_for_events);
    }
}