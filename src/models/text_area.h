#pragma once

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"

namespace models {

    typedef size_t (*finder)(const utils::Slice<uint8_t>& text, const size_t pos);
    typedef size_t (*finder_by)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step);

    class TextArea {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            size_t _capacity;
            size_t _size;
            size_t _cursor;

        public:

            explicit TextArea(const size_t capacity);

            void write(const utils::Slice<uint8_t>& data);

            utils::Slice<uint8_t> text() const;

            void clear();

            size_t position() const;

            size_t size() const;

            void move_to(const size_t pos);

            template<finder find_pos>
            void move_to() {
                _cursor = find_pos(utils::Slice(_bytes.get(), _size), _cursor);
            }

            template<finder_by find_pos>
            void move_to(const size_t step = 1) {
                _cursor = find_pos(utils::Slice(_bytes.get(), _size), _cursor, step);
            }

    };

    struct TextCursor {
        utils::Position pos;
        size_t n_lines;
    };    
}