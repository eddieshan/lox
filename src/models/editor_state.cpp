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

Range<size_t> slide_window_down(const Slice<uint8_t> text, const size_t new_pos, const size_t rows) {
    const auto new_end = slice::find(text, ascii::Lf, new_pos);
    const auto new_start = slice::find_n_back(text, ascii::Lf, new_end, rows);
    return Range<size_t> { start: new_start, end: new_end };
}

Range<size_t> slide_window_up(const Slice<uint8_t> text, const size_t new_pos, const size_t rows) {
    const auto new_start = slice::find_back(text, ascii::Lf, new_pos);
    const auto new_end = slice::find_n(text, ascii::Lf, new_start, rows);
    return Range<size_t> { start: new_start, end: new_end };    
}

void EditorState::update(const size_t new_pos) {
    const auto text = text_area.text();

    if(new_pos > visible_region.end) {
        visible_region = slide_window_down(text, new_pos, window_size.rows);
    } else if(new_pos < visible_region.start) {
        visible_region = slide_window_up(text, new_pos, window_size.rows);
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