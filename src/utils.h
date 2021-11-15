#ifndef UTILS_H
#define UTILS_H

namespace utils {
    template<typename T>
    struct Slice {
        const T* data;
        const size_t size;
    };
}

#endif

