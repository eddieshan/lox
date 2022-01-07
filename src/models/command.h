#pragma once

#include <cstdint>
#include "../utils/slice.h"
#include "../utils/array_list.h"

namespace models {

    using Navigator = size_t (*)(const utils::Slice<uint8_t>& text, const size_t current_pos);    

    enum class CommandType {
        OpenFile
    };

    class Command {
        private:
            CommandType _type;
            utils::ArrayList<uint8_t> _text;
            size_t _pos;

        public:

            explicit Command(const size_t command_line_size);

            size_t pos() const;
            CommandType type() const;
            utils::Slice<uint8_t> text() const;

            void set(const CommandType command_type);
            void move(const Navigator navigate);
            void insert(const uint8_t val);
            void erase();
    };
}