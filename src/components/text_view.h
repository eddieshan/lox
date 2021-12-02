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

            template<typename TResult>
            TResult map(TResult (*mapper)(const utils::Slice<uint8_t>& text, const size_t pos)) const {
                return mapper(utils::Slice(_bytes.get(), _length), _cursor);
            }

            size_t position() const;

            size_t length() const;

            void move_to(const size_t pos);

            void move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos));

            void move_to(size_t (*find_pos)(const utils::Slice<uint8_t>& text, const size_t pos, const size_t step), const size_t step = 1);
    };
}

#endif