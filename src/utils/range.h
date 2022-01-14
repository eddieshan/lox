#pragma once

#include <cstddef>

namespace utils {

    template<typename TComparable>
    struct Range {
        TComparable start;
        TComparable end;
    };
    
    namespace range {
        template<typename TComparable>
        bool any(const Range<TComparable>& range, const TComparable val) {
            return val >= range.start && val <= range.end;
        }

        template<typename TComparable>
        size_t size(const Range<TComparable>& range) {
            return range.start == range.end? 0 : range.end - range.start + 1;
        }
    }
}