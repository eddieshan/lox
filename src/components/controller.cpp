#include "../utils/ascii.h"
#include "../term/term.h"
#include "../text/navigation.h"
#include "../models/text_area.h"
#include "common.h"
#include "controller.h"

using namespace components;
using namespace utils;
using namespace text;
using namespace models;

bool controller::process(const term::Key& key, EditorState& state) {

    switch (key.code) {
        case ascii::CtrlQ:
            return false;
            break;
        case ascii::Cr:
            break;
        case ascii::Up:
            state.text_area.move_to<navigation::row_back>();
            break;
        case ascii::Down:
            state.text_area.move_to<navigation::row_forward>();
            break;
        case ascii::Right:
            state.text_area.move_to<navigation::col_forward>();
            break;
        case ascii::Left:
            state.text_area.move_to<navigation::col_back>();
            break;
        case ascii::Htab:
            break;
        case ascii::LnStart:
            state.text_area.move_to<navigation::row_start>();
            break;
        case ascii::LnEnd:
            state.text_area.move_to<navigation::row_end>();
            break;
        case ascii::Del:
            state.text_buffer.erase(state.text_area.position());        
            state.text_area.clear();
            state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);
            break;
        case ascii::BSpace:
            state.text_area.move_to<navigation::col_back>();
            state.text_buffer.erase(state.text_area.position());
            state.text_area.clear();
            state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);        
            break;
        default:
            if (key.size == 1) {
                const auto next_pos = state.text_buffer.insert(key.code, state.text_area.position());
                state.text_area.clear();
                state.text_buffer.accept<TextArea, &TextArea::write>(state.text_area);
                state.text_area.move_to(next_pos);
            }
    };

    return true;
}