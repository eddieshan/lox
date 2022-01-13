#pragma once

#include <cstdint>
#include <array>

#include "range.h"

namespace utils {

    // Immutable, non owned slice type.
    // It is meant to be used for sharing read only slices.
    template<typename TItem>
    struct Slice {
        TItem* data;
        size_t size;

        Slice(TItem* data_, const size_t size_): data(data_), size(size_) {}
    };

    namespace slice {

        Slice<uint8_t> from(const char* val);

        template<typename TItem>
        Slice<TItem> sub(const Slice<TItem>& slice, const Range<size_t>& range) {
            return Slice(slice.data + range.start, range::size(range));
        }

        template<typename TItem>
        size_t count(const Slice<TItem>& slice, const TItem val) {
            auto count = 0;
            for(auto i = 0; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    ++count;
                }
            }

            return count;
        }

        template<typename TItem>
        size_t count(const Slice<TItem>& slice, const TItem val, const size_t from, const size_t to) {
            auto count = 0;
            for(auto i = from; i <= to; ++i) {
                if(slice.data[i] == val) {
                    ++count;
                }
            }

            return count;
        }

        template<typename TItem>
        size_t count(const Slice<TItem>& slice, const TItem val, const Range<size_t>& range) {
            auto count = 0;
            for(auto i = range.start; i <= range.end; ++i) {
                if(slice.data[i] == val) {
                    ++count;
                }
            }

            return count;
        }

        template<typename TItem>
        bool any(const Slice<TItem>& slice, const TItem val) {
            for(auto i = 0; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    return true;
                }
            }

            return false;
        }

        template<typename TItem>
        size_t find(const Slice<TItem>& slice, const TItem val, const size_t from) {
            for(auto i = from; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    return i;
                }
            }

            return slice.size;
        }

        template<typename TItem>
        size_t find(const Slice<TItem>& slice, const TItem val, const Range<size_t>& range) {
            for(auto i = range.start; i <= range.end; ++i) {
                if(slice.data[i] == val) {
                    return i;
                }
            }

            return slice.size;
        }

        template<typename TItem>
        size_t find_n(const Slice<TItem>& slice, const TItem val, const size_t target, const size_t from = 0) {
            auto count = 0;
            for(auto i = from; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    ++count;
                    if(count == target) {
                        return i;
                    }
                }
            }

            return slice.size;
        }

        template<typename TItem>
        size_t find_back(const Slice<TItem>& slice, const TItem val, const size_t from) {
            for(size_t i = from + 1; i > 0; --i) {
                const auto actual_index = i - 1;                
                if(slice.data[actual_index] == val) {
                    return actual_index;
                }
            }

            return 0;
        }

        template<typename TItem>
        size_t find_n_back(const Slice<TItem>& slice, const TItem val, const size_t target, const size_t from = 0) {
            auto count = 0;
            for(size_t i = from + 1; i > 0; --i) {
                const auto actual_index = i - 1;
                if(slice.data[actual_index] == val) {
                    ++count;
                    if(count == target) {
                        return actual_index;
                    }
                }
            }

            return 0;
        }

        template<typename TItem, bool (*predicate)(const TItem val)>
        size_t match(const Slice<TItem>& slice) {
            auto i = 0;
            while(i < slice.size && predicate(slice.data[i])) {
                ++i;
            }

            return i;
        }


    }
}