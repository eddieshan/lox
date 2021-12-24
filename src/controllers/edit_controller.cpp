#include <fstream>

#include "../utils/array.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "../text/navigation.h"
#include "../buffers/buffer.h"
#include "../models/editor_state.h"
#include "command_controller.h"
#include "edit_controller.h"

using namespace utils;
using namespace buffers;
using namespace controllers;
using namespace text;
using namespace models;

ControllerResult edit_controller::process(const term::Key& key, EditorState& state) {

    auto result = ControllerResult {
        controller: edit_controller::process,
        exit: false,
        text_updated: false,
        active_views: active_views::Edit
    };

    switch (key.code) {
        case ascii::CtrlQ:
            result.exit = true;
            break;
        case ascii::CtrlO:
            state.command.type = CommandType::OpenFile;
            state.pos = 0;
            result.controller = command_controller::process;
            result.active_views = active_views::Edit | active_views::Command;
            break;
        case ascii::Cr:
            state.pos = state.text_buffer.insert(ascii::Lf, state.pos);
            result.text_updated = true;
            break;
        case ascii::Up:
            state.pos = navigation::row_back(state.text_area.text(), state.pos);
            break;
        case ascii::Down:
            state.pos = navigation::row_forward(state.text_area.text(), state.pos);
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
            result.text_updated = true;
            break;
        case ascii::BSpace:
            state.pos = navigation::col_back(state.text_area.text(), state.pos);
            state.text_buffer.erase(state.pos);
            result.text_updated = true;
            break;
        default:
            if (key.size == 1) {
                state.pos = state.text_buffer.insert(key.code, state.pos);
                result.text_updated = true;
            }
    };

    return result;
}