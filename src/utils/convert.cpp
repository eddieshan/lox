#include <cstdint>
#include <cstddef>

#include "convert.h"

namespace utils::convert {
    // Converts a size_t of 1 to 3 digits to chars.
    // The result is right aligned in the target.
    // Absent digits have no effect in the corresponding target position 
    // e.g. for absent digit n, the position n at target is left untouched.
    // The caller is expected to pass a value with the right number of digits.
    // If val has more than 3 digits, the result is undefined.
    void to_chars_3(const size_t val, uint8_t* target) {
        const auto d0 = val/100;
        const auto d0_rest = val%100;
        const auto d1 = d0_rest/10;
        const auto d2 = d0_rest%10;

        if(d0 != 0) {
            target[0] = d0 + 48;
        }

        if(d1 != 0 || d0 != 0) {
            target[1] = d1 + 48;
        }

        if(d2 != 0 || d1 != 0) {
            target[2] = d2 + 48;
        }
    }
}