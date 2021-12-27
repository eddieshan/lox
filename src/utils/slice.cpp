#include <cstring>
#include "slice.h"

using namespace utils;

// This implementation is a bit odd and not totally safe.
// slice::from main use is to return slices from string literals, this 
// works because string literals have static storage for the 
// duration of the program.
// Since the caller receiving the slice is not required to know this,
// should it try to write on the slice mem block, which would be a 
// read-only area since it belongs to a string literal. 
// This is a corner case since slice is meant to be used for sharing 
// mem slices as read only so writing on the slice is a no-no.
// TODO: despite being a corner case, the function introduces a potential
// memory issue. Consider this implementation convenient but temporary.
// A better solution is needed, true immutable slices using pointer 
// constness propagation might do.
Slice<uint8_t> slice::from(const char* val) {
    const auto size = std::strlen(val);
    return Slice((uint8_t*)val, size);
}