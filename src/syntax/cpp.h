#include "../utils/slice.h"
#include "../utils/array.h"

namespace syntax::cpp {

    constexpr auto Delimiter = (uint8_t)' ';

    const char Keywords[] = "return|if|else|switch|break|while|for|using|#include|new|delete";
    const char TypeKeywords[] = "const|auto|namespace|void|int|char|double|long|class|struct";
}