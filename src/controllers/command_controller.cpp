#include "../utils/ascii.h"
#include "../utils/units.h"
#include "../utils/range.h"
#include "../term/term.h"
#include "../buffers/piece_table.h"
#include "../text/navigation.h"
#include "../models/editor_state.h"
#include "controllers.h"

using namespace utils;
using namespace buffers;
using namespace controllers;
using namespace text;
using namespace models;

ControllerResult controllers::command_line(const term::Key& key, EditorState& state) {

    auto result = ControllerResult {
        controller: controllers::command_line,
        view: views::command_line,
        exit: false
    };

    switch (key.code) {
        case ascii::CtrlQ:
            result.exit = true;
            break;
        case ascii::Esc:
            result.controller = controllers::edit;
            result.view = views::edit;
            break;            
        case ascii::CtrlO:
            state.command.set(CommandType::OpenFile);
            break;
        case ascii::Cr:
            state.execute_command();
            result.controller = controllers::edit;
            result.view = views::edit;
            break;
        case ascii::Right:
            state.command.move(navigation::col::right);
            break;
        case ascii::Left:
            state.command.move(navigation::col::left);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.command.move(navigation::row::start);
            break;
        case ascii::LnEnd:
            state.command.move(navigation::row::end);
            break;
        case ascii::Del:
            state.command.erase();
            break;
        case ascii::BSpace:
            state.command.move(navigation::col::left);
            state.command.erase();
            break;
        default:
            if (key.size == 1) {
                state.command.insert(key.code);
            }
    };

    return result;
}