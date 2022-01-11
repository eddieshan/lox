#pragma once

#include <cstddef>
#include <cstring>
#include <memory>

#include "slice.h"
#include "array_buffer.h"

namespace utils
{
    // A list container implemented on an owned, heap allocated array,
    // - Capacity is fixed and set during construction so it cannot grow.
    // - Insertions have no effect when capacity is reached.
    // - Only adequate for TriviallyCopyable items.
    // - Items are guaranteed to be contiguous in memory.
    // - Insert and erase operations involve mem copying.
    template<typename TItem>
    class ArrayList {
        private:
            utils::ArrayBuffer<TItem> _array;

        public:
            explicit ArrayList(const size_t capacity):
                _array(capacity) {}

            ArrayList(const ArrayList& other) = delete;
            ArrayList& operator=(const ArrayList& other) = delete;

            ArrayList(ArrayList&& other):
                _array(std::move(other._array)) {}

            ArrayList& operator=(ArrayList&& other) = delete;

            ~ArrayList() = default;

            void insert(const TItem& item, const size_t pos) {
                if(_array.size < _array.capacity() && pos >= 0 && pos <= _array.size) {
                    auto data = _array.data();

                    if(pos < _array.size) {
                        std::copy(data + pos, data + _array.size, data + pos + 1);
                    }
                    data[pos] = item;

                    ++_array.size;
                }
            }

            void erase(const size_t pos) {
                if(pos >= 0 && pos < _array.size) {
                    auto data = _array.data();

                    if(pos < _array.size) {
                        std::copy(data + pos + 1, data + _array.size, data + pos);
                    }

                    --_array.size;
                }
            }

            void clear() {
                std::memset(_array.data(), 0, _array.capacity()*sizeof(TItem));
                _array.size = 0;
            }

            void insert(const TItem& item) {
                if(_array.size < _array.capacity()) {
                    _array.data()[_array.size] = item;
                    ++_array.size;
                }
            }

            utils::Slice<TItem> data() const {
                return utils::Slice<TItem>(_array.data(), _array.size);
            }

            TItem& operator[](const size_t pos) { 
                return _array.data()[pos]; 
            }

            TItem& operator[](const size_t pos) const { 
                return _array.data()[pos]; 
            }

            size_t size() const { 
                return _array.size; 
            }

            size_t capacity() const { 
                return _array.capacity(); 
            }
    };    
}