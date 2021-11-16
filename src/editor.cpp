#include <stdio.h>

#include "editor.h"
#include "term.h"
#include "keys.h"
#include "ansi.h"
#include "gap_buffer.h"
#include "fixed_buffer.h"

Editor::Editor() {
}

Editor& Editor::instance()
{
    static Editor instance;
    return instance;
}

void Editor::start() {
    
    if(!_state.is_started) {
        GapBuffer text_buffer;
        FixedBuffer screen_buffer;

        const auto result = term::enable_raw_mode();

        while (1) {

            const auto key = term::read_key();

            switch (key.code) {
                case keys::CtrlQ:
                    return;
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
                        text_buffer.insert(key.code);
                    }
            };

            screen_buffer.write<term::ansi::Clear.size()>(term::ansi::Clear);
            screen_buffer.write<term::ansi::Home.size()>(term::ansi::Home);

            text_buffer.accept<FixedBuffer>(&FixedBuffer::write, screen_buffer);
            screen_buffer.accept(term::write_bytes);

            term::flush();
            screen_buffer.clear();
        }  
    }
}