#include <fstream>

#include "../utils/array.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "../text/navigation.h"
#include "../buffers/buffer.h"
#include "../models/editor_state.h"
#include "controller.h"

using namespace utils;
using namespace buffers;
using namespace controllers;
using namespace text;
using namespace models;

void open_file(EditorState& state, const char* path) {

    state.command.text.write(path);

    std::ifstream reader(path, std::ifstream::in);

    auto pos = 0;

    while (reader.good()) {
        const auto c = reader.get();
        pos = state.text_buffer.insert(c, pos);
    }

    reader.close();
}

bool controller::process(const term::Key& key, EditorState& state) {

    auto text_changed = false;
    const auto path = "/home/dev/development/test.cpp";

    switch (key.code) {
        case ascii::CtrlQ:
            return false;
            break;
        case ascii::CtrlO:
            //const auto path = "/home/dev/Downloads/piecechain/SpanView.h";
            //printf("Open: %s", path);
            open_file(state, path);
            text_changed = true;
            state.pos = 0;
            break;
        case ascii::Cr:
            break;
        case ascii::Up:
            state.pos = navigation::row_back(state.text_area.text(), state.pos, 1);
            break;
        case ascii::Down:
            state.pos = navigation::row_forward(state.text_area.text(), state.pos, 1);
            break;
        case ascii::Right:
            state.pos = navigation::col_forward(state.text_area.text(), state.pos);
            break;
        case ascii::Left:
            state.pos = navigation::col_back(state.text_area.text(), state.pos);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.pos = navigation::row_start(state.text_area.text(), state.pos);
            break;
        case ascii::LnEnd:
            state.pos = navigation::row_end(state.text_area.text(), state.pos);            
            break;
        case ascii::Del:
            state.text_buffer.erase(state.pos);
            text_changed = true;
            break;
        case ascii::BSpace:
            state.pos = navigation::col_back(state.text_area.text(), state.pos);
            state.text_buffer.erase(state.pos);
            text_changed = true;
            break;
        default:
            if (key.size == 1) {
                state.pos = state.text_buffer.insert(key.code, state.pos);
                state.text_buffer.erase(state.pos);
                text_changed = true;                
            }
    };

    if(text_changed) {
        state.text_area.clear();
        state.text_buffer.accept<Buffer, &Buffer::write>(state.text_area);
    }

    return true;
}