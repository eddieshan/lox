#pragma once

#include <cstdint>
#include <array>

namespace utils {

    // Immutable, non owned slice type.
    // It is meant to be used for sharing read only slices.
    template<typename T>
    struct Slice {
        T* data;
        size_t size;

        Slice(T* data_, const size_t size_): data(data_), size(size_) {}
    };

    namespace slice {

        Slice<uint8_t> from(const char* val);

        template<typename T>
        bool contains(const Slice<T>& slice, const T val) {
            for(auto i = 0; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    return true;
                }
            }

            return false;
        }

    }
}