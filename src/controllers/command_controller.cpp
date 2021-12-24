#include <fstream>

#include "../utils/array.h"
#include "../utils/slice.h"
#include "../utils/ascii.h"
#include "../term/term.h"
#include "../text/navigation.h"
#include "../buffers/buffer.h"
#include "../models/editor_state.h"
#include "common.h"
#include "edit_controller.h"
#include "command_controller.h"

using namespace utils;
using namespace buffers;
using namespace controllers;
using namespace text;
using namespace models;

void open_file(EditorState& state) {

    const auto path = (char*)state.command.text.data().data;

    std::ifstream reader(path, std::ifstream::in);

    auto pos = 0;

    while (reader.good()) {
        const auto c = reader.get();
        pos = state.text_buffer.insert(c, pos);
    }

    reader.close();
}

void execute_command(EditorState& state) {
    if(state.command.type == CommandType::OpenFile) {
        open_file(state);
        state.pos = 0;
    }
}

ControllerResult command_controller::process(const term::Key& key, EditorState& state) {

    auto result = ControllerResult {
        controller: command_controller::process,
        exit: false,
        text_updated: false,
        active_views: active_views::Command | active_views::Edit
    };

    switch (key.code) {
        case ascii::CtrlQ:
            result.exit = true;
            break;
        case ascii::Esc:
            result.controller = edit_controller::process;
            result.active_views = active_views::Edit;
            break;            
        case ascii::CtrlO:
            state.command.type = CommandType::OpenFile;
            state.pos = 0;
            break;
        case ascii::Cr:
            execute_command(state);
            result.text_updated = true;
            result.controller = edit_controller::process;
            result.active_views = active_views::Edit;
            break;
        case ascii::Right:
            state.pos = navigation::col_forward(state.command.text.data(), state.pos);
            break;
        case ascii::Left:
            state.pos = navigation::col_back(state.command.text.data(), state.pos);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.pos = navigation::row_start(state.command.text.data(), state.pos);
            break;
        case ascii::LnEnd:
            state.pos = navigation::row_end(state.command.text.data(), state.pos);
            break;
        case ascii::Del:
            state.command.text.erase(state.pos);
            break;
        case ascii::BSpace:
            state.pos = navigation::col_back(state.text_area.text(), state.pos);
            state.command.text.erase(state.pos);
            break;
        default:
            if (key.size == 1) {
                state.command.text.insert(key.code, state.pos);
                ++state.pos;
                result.text_updated = true;
            }
    };

    return result;
}