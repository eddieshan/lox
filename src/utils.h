#ifndef UTILS_H
#define UTILS_H

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
}

#endif

