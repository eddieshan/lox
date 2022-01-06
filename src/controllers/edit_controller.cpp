#include <fstream>

#include "../utils/ascii.h"
#include "../term/term.h"
#include "../text/navigation.h"
#include "../models/editor_state.h"
#include "controllers.h"

using namespace utils;
using namespace controllers;
using namespace text;
using namespace models;

ControllerResult controllers::edit(const term::Key& key, EditorState& state) {

    auto result = ControllerResult {
        controller: controllers::edit,
        view: views::edit,
        exit: false,
        text_updated: false
    };

    switch (key.code) {
        case ascii::CtrlQ:
            result.exit = true;
            break;
        case ascii::CtrlO:
            state.command.type = CommandType::OpenFile;
            state.pos = 0;
            result.controller = controllers::command_line;
            result.view = views::command_line;
            break;
        case ascii::Cr:
            state.update(state.text_buffer.insert(ascii::Lf, state.pos));
            result.text_updated = true;
            break;
        case ascii::Up:
            state.update(navigation::row::up(state.text_area.text(), state.pos));
            break;
        case ascii::Down:
            state.update(navigation::row::down(state.text_area.text(), state.pos));
            break;
        case ascii::Right:
            state.update(navigation::col::right(state.text_area.text(), state.pos));
            break;
        case ascii::Left:
            state.update(navigation::col::left(state.text_area.text(), state.pos));
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.update(navigation::row::start(state.text_area.text(), state.pos));
            break;
        case ascii::LnEnd:
            state.update(navigation::row::end(state.text_area.text(), state.pos));
            break;
        case ascii::Del:
            state.text_buffer.erase(state.pos);
            result.text_updated = true;
            break;
        case ascii::BSpace:
            state.pos = navigation::col::left(state.text_area.text(), state.pos);
            state.text_buffer.erase(state.pos);
            result.text_updated = true;
            break;
        default:
            if (key.size == 1) {
                //state.pos = state.text_buffer.insert(key.code, state.pos);
                state.update(state.text_buffer.insert(key.code, state.pos));
                result.text_updated = true;
            }
    };

    return result;
}