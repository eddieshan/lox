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

    template<std::size_t Size>
    constexpr size_t sum(const size_t (&array)[Size]) {
        auto sum = 0;
        for (auto v : array) {
            sum += v;
        }
        return sum;
    };

    template <typename T, size_t... Size>
    constexpr auto concat(std::array<T, Size>... array)
    {
        constexpr size_t n_arrays = sizeof...(array);
        constexpr size_t sizes[n_arrays] {array.size()...};

        T* expanded_arrays[n_arrays] = {&array[0]...};

        constexpr auto total_size = sum(sizes);

        std::array<T, total_size> result = {0};

        auto index = 0;
        for(auto i = 0; i < n_arrays; i++)
        {
            for(auto j = 0; j < sizes[i]; j++)
            {
                result[index] = expanded_arrays[i][j];
                index++;
            }
        }

        return result;
    }     
}

#endif

