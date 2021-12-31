#include <array>

namespace syntax::cpp {

    constexpr auto Delimiters = " ,;{}()";

    constexpr auto StringDelimiters = "\"|\"|\'|\'";
    constexpr auto CommentDelimiters = "//||/*|*/";

    constexpr auto Keywords = "return|if|else|switch|break|while|for|using|#include|new|delete";
    constexpr auto TypeKeywords = "const|auto|namespace|void|unsigned|int|char|double|long|class|struct";
    constexpr auto Operators = "+-*/%<>=[]&|~?:";
}