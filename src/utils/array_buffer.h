#pragma once

#include <cstddef>
#include <memory>

namespace utils {

    // ArrayBuffer is an owned, fixed size, heap allocated array with size and max capacity.
    // Size is exposed as an open property, the class user is responsible for its consistency.
    // I chose not to use std::vector because,
    // - I needed a non-growable container,
    // - calling items destructors upon release was not desired,
    // - in general, std::vector has overhead I preferred to avoid.
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

            size_t capacity() const {
                return _capacity;
            }

            TItem* data() const {
                return _data.get();
            }            
    };
}