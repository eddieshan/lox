#include "../utils/slice.h"
#include "common.h"
#include "command.h"

using namespace utils;
using namespace models;

Command::Command(const size_t command_line_size):
    _text(ArrayList<uint8_t>(command_line_size)),
    _type(CommandType::OpenFile),
    _pos(0) {}

size_t Command::pos() const {
    return _pos;
}

CommandType Command::type() const {
    return _type;
}

Slice<uint8_t> Command::text() const {
    return _text.data();
}

void Command::set(const CommandType command_type) {
    _type = CommandType::OpenFile;
    _pos = 0;
}

void Command::move(const Navigator navigate) {
    _pos = navigate(_text.data(), _pos);
}

void Command::insert(const uint8_t val) {
    _text.insert(val);
    ++_pos;
}

void Command::erase() {
    _text.erase(_pos);
}
