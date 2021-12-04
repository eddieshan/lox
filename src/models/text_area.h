#ifndef TEXT_AREA_H
#define TEXT_AREA_H

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"
#include "../buffers/fixed_buffer.h"

namespace models {

    class TextArea {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            size_t _size;
            size_t _length;
            size_t _cursor;

        public:

            TextArea(size_t size);

            void write(const utils::Slice<uint8_t>& data);

            utils::Slice<uint8_t> text() const;

            void clear();

            size_t position() const;

            size_t length() const;

            void move_to(const size_t pos);

            void move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos));

            void move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step), const size_t step = 1);
    };
}

#endif