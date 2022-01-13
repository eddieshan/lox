#include "../utils/range.h"

namespace syntax::cpp {

    constexpr auto Delimiters = " ,;{}()";

    constexpr auto StringDelimiters = "\"|\"|\'|\'";
    constexpr auto CommentDelimiters = "//||/*|*/";
    constexpr auto FunctionCallDelimiters = utils::Range<uint8_t> { start: (uint8_t)'(', end: (uint8_t)')'};

    constexpr auto Keywords = "return|if|else|switch|break|do|while|for|using|#include|new|delete";
    constexpr auto TypeKeywords = "constexpr|const|auto|namespace|void|unsigned|bool|byte|int|char|double|long|enum|class|struct|template";
    constexpr auto Operators = "+-*/%<>=[]&|~?:";
}