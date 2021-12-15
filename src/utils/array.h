#pragma once

#include <array>

namespace utils::array {

    template <typename V, typename... T>
    constexpr auto from(T&&... t)
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
        for(auto i = 0; i < n_arrays; ++i)
        {
            for(auto j = 0; j < sizes[i]; ++j)
            {
                result[index] = expanded_arrays[i][j];
                ++index;
            }
        }

        return result;
    }

    template<std::size_t Size>
    constexpr std::array<uint8_t, Size - 1> to_uint8_t(const char (&chars)[Size]) {
        constexpr auto new_size = Size - 1;
        std::array<uint8_t, new_size> result { };

        for(auto i = 0; i < new_size; ++i) {
            result[i] = (uint8_t)chars[i];
        }

        return result;
    };    
}