#include <array>

namespace syntax::cpp {

    constexpr auto Delimiters = std::array<uint8_t, 6> { ' ', ';', '{', '}', '(', ')' };

    constexpr char Keywords[] = "return|if|else|switch|break|while|for|using|#include|new|delete";
    constexpr char TypeKeywords[] = "const|auto|namespace|void|int|char|double|long|class|struct";
}