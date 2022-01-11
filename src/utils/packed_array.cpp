#include <cstddef>
#include <memory>
#include <cstring>

#include "slice.h"
#include "packed_array.h"

using namespace utils;

namespace utils
{
    PackedArray::PackedArray(const size_t capacity):
        _array(capacity),
        _n_items(0) {}

    PackedArray::PackedArray(PackedArray&& other) noexcept:
        _array(std::move(other._array)),
        _n_items(other._n_items) {}

    void PackedArray::append(const uint8_t* first, const uint8_t* last) {
        const auto remaining = _array.capacity() - _array.size;
        const auto data_size = last - first;
        const auto data = _array.data();

        if(remaining > data_size) {
            data[_array.size] = data_size;
            ++_array.size;
            std::copy(first, last, data + _array.size);
            _array.size += data_size;
            ++_n_items;
        }
    }

    void PackedArray::clear() {
        std::memset(_array.data(), 0, _array.capacity()*sizeof(uint8_t));
        _array.size = 0;
    }

    PackedArray::PackedArrayIterator::PackedArrayIterator(const PackedArray& packed_array):
        _packed_array(packed_array),
        _pos(0) {}

    Slice<uint8_t> PackedArray::PackedArrayIterator::next() {
        const auto data = _packed_array._array.data();
        if(_pos < _packed_array._array.size) {
            const auto item_size = data[_pos];
            const auto item_start = _pos + 1;
            const auto slice = Slice(data + item_start, item_size);
            _pos = item_start + item_size;
            return slice;
        } else {
            return Slice(data, 0);
        }
    }
}