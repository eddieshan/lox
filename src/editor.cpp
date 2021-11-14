#include <stdio.h>

#include "editor.h"
#include "term.h"
#include "keys.h"
#include "ansi.h"
#include "gap_buffer.h"

Editor::Editor() {
}

Editor& Editor::instance()
{
    static Editor instance;
    return instance;
}

void Editor::start() {
    
    if(!_state.is_started) {
        GapBuffer buffer;
        const auto result = term::enable_raw_mode();

        term::write_bytes((char*)term::ansi::Clear, sizeof(term::ansi::Clear));
        term::write_bytes((char*)term::ansi::Home, sizeof(term::ansi::Home));
        term::flush();

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
                        buffer.insert(key.code);
                    }
            };

            term::write_bytes((char*)term::ansi::Clear, sizeof(term::ansi::Clear));
            term::write_bytes((char*)term::ansi::Home, sizeof(term::ansi::Home));

            buffer.visit(term::write_bytes);

            term::flush();
        }  
    }
}