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

        Slice(T* data_, size_t size_): data(data_), size(size_) {}
    };

    template <typename V, typename... T>
    constexpr auto array_of(T&&... t)
        -> std::array<V, sizeof...(T)>
    {
        return {{ std::forward<T>(t)... }};
    }
}

#endif

