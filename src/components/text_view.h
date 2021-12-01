#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <memory>

#include "../utils/geometry.h"
#include "../utils/slice.h"

namespace components {

    class TextView {
        private:
            std::unique_ptr<uint8_t[]> _bytes;
            size_t _size;
            size_t _length;
            size_t _cursor;

        public:
            TextView(size_t size);

            void write(const utils::Slice<uint8_t>& data);

            void render(void (*write)(const utils::Slice<uint8_t>&));

            void clear();

            utils::Position screen_position() const;

            size_t position() const;

            size_t length() const;

            void move_to(const size_t pos);

            void col_forward();

            void col_back();

            void row_forward(const size_t step = 1);

            void row_back(const size_t step = 1);
    };

}

#endif