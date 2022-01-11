#pragma once

#include <cstddef>
#include <memory>

#include "slice.h"
#include "array_buffer.h"

namespace utils
{
    // PackedArray: an owned, heap allocated array for binary segments of arbitrary length.
    // It is meant to be used for compact octet representations of any kind of data. 
    // Octet at position 0 contains the length n of the first segment,
    // the next n octets correspond to the first segment.
    // n + 1 contains the length n of the second segment and so on.
    class PackedArray {
        private:
            utils::ArrayBuffer<uint8_t> _array;
            size_t _n_items;

        public:
            explicit PackedArray(const size_t capacity);

            PackedArray(const PackedArray& other) = delete;
            PackedArray& operator=(const PackedArray& other) = delete;

            PackedArray(PackedArray&& other) noexcept;
            PackedArray& operator=(PackedArray&& other) = delete;

            ~PackedArray() = default;

            void append(const uint8_t* first, const uint8_t* last);

            void clear();

            class PackedArrayIterator {
                private:
                    const PackedArray& _packed_array;
                    size_t _pos;
                
                public:
                    explicit PackedArrayIterator(const PackedArray& packed_array);
                    utils::Slice<uint8_t> next();
            };
    };
}