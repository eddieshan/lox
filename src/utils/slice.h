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
            return Slice(slice.data + range.start, range.end - range.start + 1);
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
        bool contains(const Slice<TItem>& slice, const TItem val) {
            for(auto i = 0; i < slice.size; ++i) {
                if(slice.data[i] == val) {
                    return true;
                }
            }

            return false;
        }

        template<typename TItem, bool (*predicate)(const TItem val)>
        size_t find(const Slice<TItem>& slice) {
            for(auto i = 0; i < slice.size; ++i) {
                if(predicate(slice.data[i])) {
                    return i;
                }
            }

            return slice.size;
        }

        template<typename TItem, bool (*predicate)(const TItem val)>
        size_t find(const Slice<TItem>& slice, const size_t from, const size_t to) {
            for(auto i = from; i <= to; ++i) {
                if(predicate(slice.data[i])) {
                    return i;
                }
            }

            return slice.size;
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
        size_t find_n(const Slice<TItem>& slice, const TItem val, const size_t target) {
            auto count = 0;
            for(auto i = 0; i < slice.size; ++i) {
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
        size_t find_n(const Slice<TItem>& slice, const TItem val, const size_t from, const size_t target) {
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
                if(slice.data[i - 1] == val) {
                    return i;
                }
            }

            return 0;
        }

        template<typename TItem>
        size_t find_n_back(const Slice<TItem>& slice, const TItem val, const size_t from, const size_t target) {
            auto count = 0;
            for(size_t i = from + 1; i > 0; --i) {
                if(slice.data[i - 1] == val) {
                    ++count;
                    if(count == target) {
                        return i;
                    }
                }
            }

            return 0;
        }

    }
}