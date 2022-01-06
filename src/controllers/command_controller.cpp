#include <fstream>

#include "../utils/ascii.h"
#include "../utils/units.h"
#include "../utils/range.h"
#include "../utils/io.h"
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

void open_file(EditorState& state, const char* path) {

    const auto size = io::file_size(path);

    if(size <= state.text_buffer.capacity()) {
        std::ifstream reader(path, std::ifstream::in);

        auto pos = 0;

        // TODO: using a temporary read buffer is not optimal.
        // Reads could be done directly onto the underlying buffer of the piece table. 
        // The problem with this is doing this safely, memory wise e.g. exposing a 
        // pointer to the underlying buffer would be straightforward but clearly unsafe,
        // An alternative would be using a templated visitor but the signature for 
        // ifstream::read would introduce undesired depedencies to ifstream types in 
        // PieceTable, so no ideal solution yet. Needs more investigation.
        char buffer[units::Kb];

        state.text_buffer.clear();

        while (reader.good()) {
            reader.read(buffer, units::Kb);
            const auto read_size = reader.gcount();
            state.text_buffer.append(Slice((uint8_t*)buffer, read_size));
        }

        reader.close();

        state.text_area.clear();
        state.text_buffer.accept<Buffer, &Buffer::write>(state.text_area);
        state.visible_region = Range<size_t> {
            start: 0,
            end: slice::find_n(state.text_area.text(), ascii::Lf, state.window_size.rows)
        };
    }
}

void execute_command(EditorState& state) {
    if(state.command.type == CommandType::OpenFile) {
        const auto path = (char*)state.command.text.data().data;

        open_file(state, path);
        state.pos = 0;
    }
}

ControllerResult controllers::command_line(const term::Key& key, EditorState& state) {

    auto result = ControllerResult {
        controller: controllers::command_line,
        view: views::command_line,
        exit: false,
        text_updated: false
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
            state.command.type = CommandType::OpenFile;
            state.pos = 0;
            break;
        case ascii::Cr:
            execute_command(state);
            result.text_updated = true;
            result.controller = controllers::edit;
            result.view = views::edit;
            break;
        case ascii::Right:
            state.pos = navigation::col::right(state.command.text.data(), state.pos);
            break;
        case ascii::Left:
            state.pos = navigation::col::left(state.command.text.data(), state.pos);
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.pos = navigation::row::start(state.command.text.data(), state.pos);
            break;
        case ascii::LnEnd:
            state.pos = navigation::row::end(state.command.text.data(), state.pos);
            break;
        case ascii::Del:
            state.command.text.erase(state.pos);
            break;
        case ascii::BSpace:
            state.pos = navigation::col::left(state.text_area.text(), state.pos);
            state.command.text.erase(state.pos);
            break;
        default:
            if (key.size == 1) {
                state.command.text.insert(key.code, state.pos);
                ++state.pos;
            }
    };

    return result;
}