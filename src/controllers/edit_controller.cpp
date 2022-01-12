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

ActionResult controllers::edit(const term::Key& key, EditorState& state) {

    auto result = ActionResult {
        controller: controllers::edit,
        view: views::edit
    };

    switch (key.code) {
        case ascii::CtrlO:
            state.command.set(CommandType::OpenFile);
            result.controller = controllers::command_line;
            result.view = views::command_line;
            break;
        case ascii::Cr:
            state.insert(ascii::Lf);
            break;
        case ascii::Up:
            state.move(navigation::row::up);
            break;
        case ascii::Down:
            state.move(navigation::row::down);
            break;
        case ascii::Right:
            state.move(navigation::col::right);
            break;
        case ascii::Left:
            state.move(navigation::col::left);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.move(navigation::row::start);
            break;
        case ascii::LnEnd:
            state.move(navigation::row::end);
            break;
        case ascii::Del:
            state.erase();
            break;
        case ascii::BSpace:
            state.move(navigation::col::left);
            state.erase();
            break;
        default:
            if (key.size == 1) {
                state.insert(key.code);
            }
    };

    return result;
}