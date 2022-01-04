#include "../utils/units.h"
#include "../utils/ascii.h"
#include "../utils/range.h"
#include "../utils/array_list.h"
#include "../buffers/piece_table.h"
#include "../buffers/buffer.h"
#include "../term/term.h"

#include "command.h"
#include "editor_state.h"

using namespace utils;
using namespace models;
using namespace buffers;
using namespace term;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto TempTextBufferSize = 64*units::Kb;
constexpr auto CommandLineSize = 1000;

void EditorState::update(const size_t new_pos) {
    if(!range::contains(visible_region, new_pos)) {
        const auto text = text_area.text();

        if(new_pos > visible_region.end) {
            const auto new_end = slice::find(text, ascii::Lf, new_pos);
            const auto new_start = slice::find_n_back(text, ascii::Lf, new_end, window_size.rows);

            //printf("[%d, %d, %d]", new_start, new_pos, new_end);

            visible_region.start = new_start;
            visible_region.end = new_end;
        } else if(new_pos < visible_region.start) {

            const auto new_start = slice::find_back(text, ascii::Lf, new_pos);            
            const auto new_end = slice::find_n(text, ascii::Lf, new_start, window_size.rows);

            visible_region.start = new_start;
            visible_region.end = new_end;
        }
    }

    pos = new_pos;
}

EditorState editor_state::build() {
    return EditorState {
        text_buffer: PieceTable(TextBufferSize),
        text_area: Buffer(TempTextBufferSize),
        pos: 0,
        visible_region: Range<size_t> { start: 0, end: 0 },
        window_size: term::get_window_size(),
        command: Command {
            type: CommandType::OpenFile,
            text: ArrayList<uint8_t>(CommandLineSize)
        }
    };
}