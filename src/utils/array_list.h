#pragma once

#include <cstddef>
#include <memory>

#include "slice.h"

namespace utils
{
    // A list container implemented on an owned, heap allocated array.
    // Capacity is fixed and set during construction so it cannot grow.
    // Insertions have no effect when capacity is reached.
    // Since items are stored in a contiguous memory block,
    // insert and erase operations involve mem copying.
    template<typename TItem>
    class ArrayList {
        private:
            std::unique_ptr<TItem[]> _data;
            size_t _capacity;
            size_t _size;

        public:
            ArrayList(const size_t size):
                _data(std::make_unique<TItem[]>(size)),
                _capacity(size),
                _size(0) {}

            void insert(const TItem& item, const size_t pos) {
                if(_size < _capacity && pos >= 0 && pos <= _size) {
                    auto data = _data.get();

                    if(pos < _size) {
                        std::copy(data + pos, data + _size, data + pos + 1);
                    }
                    data[pos] = item;

                    ++_size;
                }
            }

            void erase(const size_t pos) {
                if(pos >= 0 && pos < _size) {
                    auto data = _data.get();

                    if(pos < _size) {
                        std::copy(data + pos + 1, data + _size, data + pos);
                    }

                    --_size;
                }
            }

            void insert(const TItem& item) {
                if(_size < _capacity) {
                    _data[_size] = item;
                    ++_size;
                }
            }

            utils::Slice<TItem> data() const {
                return utils::Slice<TItem>(_data.get(), _size);
            }

            TItem& operator[](const size_t pos) { 
                return _data[pos]; 
            }

            TItem& operator[](const size_t pos) const { 
                return _data[pos]; 
            }

            size_t size() const { 
                return _size; 
            }            
    };    
}