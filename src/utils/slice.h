#pragma once

#include <array>

namespace utils {

    // Immutable slice type.
    // Copy assignment and move assignment are disabled by making properties const.
    // Disabling assignment is actually desirable for safer handling of memory slices.
    template<typename T>
    struct Slice {
        const T* data;
        const size_t size;

        Slice(const T* data_, const size_t size_): data(data_), size(size_) {}
    };

    namespace slice {

        // TODO:
        //  Return type can be made constexpr, is it worth it?
        //  Cost of creating slices is minimal, they will be typically in the stack.
        //  Not clear whether constexpr would be beneficial, pending analysis.
        template<typename T, std::size_t Size>
        Slice<T> from(const std::array<T, Size>& array) {
            return Slice<T>(array.data(), array.size());
        };

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