#pragma once

#include <cstdint>

namespace utils {

    template<typename TComparable>
    struct Range {
        TComparable start;
        TComparable end;
    };
    
    namespace range {
        template<typename TComparable>
        bool contains(const Range<TComparable>& range, const TComparable val) {
            return val >= range.start && val <= range.end;
        }
    }
}