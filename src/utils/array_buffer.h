#pragma once

#include <cstddef>
#include <memory>

namespace utils {

    // ArrayBuffer is an owned, fixed size, heap allocated array with size and max capacity.
    // Size is exposed as an open property, the class user is responsible for its consistency.
    // ArrayBuffer covers needs not fulfilled by std::vector,
    // - a non-growable container,
    // - it does not call items destructors upon release,
    // - very simple, less overhead than std::vector.
    template<typename TItem>
    class ArrayBuffer {
        private:
            std::unique_ptr<TItem[]> _data;
            size_t _capacity;

        public:

            size_t size;

            explicit ArrayBuffer(const size_t capacity):
                _data(std::make_unique<TItem[]>(capacity)),
                _capacity(capacity),
                size(0) {}

           ArrayBuffer(const ArrayBuffer& other) = delete;
           ArrayBuffer& operator=(const ArrayBuffer& other) = delete;

           ArrayBuffer(ArrayBuffer&& other):
                _data(std::move(other._data)),
                _capacity(other._capacity),
                size(other.size) {}

           ArrayBuffer& operator=(ArrayBuffer&& other) = delete;

           ~ArrayBuffer() = default;

            size_t capacity() const {
                return _capacity;
            }

            TItem* data() const {
                return _data.get();
            }
    };
}