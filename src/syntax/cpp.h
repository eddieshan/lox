#include "../utils/range.h"

namespace syntax::cpp {

    constexpr auto Delimiters = " ,;{}()";

    constexpr auto StringDelimiters = "\"|\"|\'|\'";
    constexpr auto CommentDelimiters = "//||/*|*/";
    constexpr auto FunctionCallDelimiters = utils::Range<uint8_t> { start: (uint8_t)'(', end: (uint8_t)')'};

    constexpr auto Keywords = 
        "return|if|else|switch|case|break|do|while|for|continue|goto|using|"
        "try|catch|throw|new|delete|default|"
        "#include|#pragma|#error|#define|#undef|#if|#elif|#else|#endif|#ifdef|#ifndef";
    constexpr auto TypeKeywords = 
        "constexpr|const|auto|namespace|void|unsigned|bool|char|byte|short|int|float|double|long|enum|"
        "class|virtual|final|override|struct|union|friend|inline|static|register|sizeof|this|"
        "template|typedef|static_cast|dynamic_cast|const_cast|reinterpret_cast|extern|asm";
    constexpr auto Operators = "+-*/%<>=[]&|~?:";
}