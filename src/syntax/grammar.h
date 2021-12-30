#pragma once

#include <memory>

namespace syntax {

    enum class TokenType: int {
        Plain = 0,
        Delimiter = 1,
        Operator = 2,
        Keyword = 3,
        TypeKeyword = 4,
        NumericLiteral = 5,
        StringLiteral = 6,
        Comment = 7
    };

    struct TokenGroup {
        std::unique_ptr<uint8_t[]> tokens;
        size_t size;
        TokenType type;
    };

    struct Grammar {
        utils::Slice<const TokenGroup> fixed_tokens;
        utils::Slice<const TokenGroup> delimited_tokens;
        utils::Slice<uint8_t> delimiters;
    };

    Grammar build();
}