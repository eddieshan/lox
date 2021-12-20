#include "../utils/array.h"

namespace syntax::cpp {

    constexpr auto Delimiters = utils::array::to_uint8_t(" ;{}()");

    constexpr char Keywords[] = "return|if|else|switch|break|while|for|using|#include|new|delete";
    constexpr char TypeKeywords[] = "const|auto|namespace|void|int|char|double|long|class|struct";
}