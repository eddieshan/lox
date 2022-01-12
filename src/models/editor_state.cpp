#include <fstream>

#include "../utils/units.h"
#include "../utils/geometry.h"
#include "../utils/ascii.h"
#include "../utils/range.h"
#include "../utils/array_list.h"
#include "../utils/io.h"
#include "../buffers/piece_table.h"
#include "../buffers/vt100_buffer.h"
#include "../term/term.h"

#include "common.h"
#include "command.h"
#include "editor_state.h"

using namespace utils;
using namespace models;
using namespace buffers;
using namespace term;

constexpr auto TextBufferSize = 64*units::Kb;
constexpr auto TempTextBufferSize = 64*units::Kb;
constexpr auto CommandLineSize = 1000;

Range<size_t> slide_window_down(const Slice<uint8_t> text, const size_t new_pos, const size_t n_rows) {
    const auto new_end = slice::find(text, ascii::Lf, new_pos);
    const auto new_start = slice::find_n_back(text, ascii::Lf, n_rows, new_end);
    return Range<size_t> { start: new_start, end: new_end };
}

Range<size_t> slide_window_up(const Slice<uint8_t> text, const size_t new_pos, const size_t n_rows) {
    const auto new_start = slice::find_back(text, ascii::Lf, new_pos);
    const auto new_end = slice::find_n(text, ascii::Lf, n_rows, new_start);
    return Range<size_t> { start: new_start, end: new_end };    
}

Slice<uint8_t> EditorState::text() const {
    return _text_area.text();
}

size_t EditorState::pos() const {
    return _pos;
}

WindowSize EditorState::window_size() const {
    return _window_size;
}

Range<size_t> EditorState::visible_region() const {
    return _visible_region;
}

void EditorState::update(const size_t new_pos) {
    const auto text = _text_area.text();

    if(new_pos > _visible_region.end) {
        _visible_region = slide_window_down(text, new_pos, _window_size.rows);
    } else if(new_pos < _visible_region.start) {
        _visible_region = slide_window_up(text, new_pos, _window_size.rows);
    }

    _pos = new_pos;
}

void EditorState::move(const Navigator navigate) {
    const auto new_pos = navigate(_text_area.text(), _pos);
    update(new_pos);
}

void EditorState::move(const StepNavigator navigate, const size_t step) {
    const auto new_pos = navigate(_text_area.text(), _pos, step);
    update(new_pos);
}

void EditorState::insert(const uint8_t val) {
    const auto new_pos = _text_buffer.insert(val, _pos);
    _text_area.clear();
    _text_buffer.accept<Vt100Buffer, &Vt100Buffer::write>(_text_area);

    const auto text = _text_area.text();
    const auto clipped_size = range::size(_visible_region);

    if(text.size > clipped_size) {
        _visible_region.end = slice::find_n(text, ascii::Lf, _window_size.rows);
    }

    update(new_pos);
}

void EditorState::erase() {
    _text_buffer.erase(_pos);
    _text_area.clear();
    _text_buffer.accept<Vt100Buffer, &Vt100Buffer::write>(_text_area);
}

void EditorState::load_file(const char* path) {
    const auto size = io::file_size(path);

    if(size <= _text_buffer.capacity()) {
        std::ifstream reader(path, std::ifstream::in);

        // TODO: using a temporary read buffer is not optimal.
        // Reads could be done directly onto the underlying buffer of the piece table. 
        // The problem with this is doing this safely, memory wise e.g. exposing a 
        // pointer to the underlying buffer would be straightforward but clearly unsafe,
        // An alternative would be using a templated visitor but the signature for 
        // ifstream::read would introduce undesired depedencies to ifstream types in 
        // PieceTable, so no ideal solution yet. Needs more investigation.
        char buffer[units::Kb];

        _text_buffer.clear();

        while (reader.good()) {
            reader.read(buffer, units::Kb);
            const auto read_size = reader.gcount();
            _text_buffer.append(Slice((uint8_t*)buffer, read_size));
        }

        reader.close();

        _text_area.clear();
        _text_buffer.accept<Vt100Buffer, &Vt100Buffer::write>(_text_area);
        _visible_region = Range<size_t> {
            start: 0,
            end: slice::find_n(_text_area.text(), ascii::Lf, _window_size.rows)
        };
        _pos = 0;
    }
}

void EditorState::execute_command() {
    if(command.type() == CommandType::OpenFile) {
        const auto path = (char*)command.text().data;

        load_file(path);
    }
}

EditorState::EditorState(const size_t buffer_size, const size_t command_size, const WindowSize& window_size):
    _text_buffer(PieceTable(TextBufferSize)),
    _text_area(Vt100Buffer(TempTextBufferSize)),
    _pos(0),
    _visible_region(Range<size_t> { start: 0, end: 0 }),
    _window_size(window_size),
    command(Command(CommandLineSize)) { }

EditorState editor_state::build() {
    return EditorState(TextBufferSize, CommandLineSize, term::get_window_size());
}