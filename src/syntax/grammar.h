#pragma once

#include <memory>

namespace syntax {

    enum class TokenType {
        Plain,
        Keyword,
        TypeKeyword,
        NumericLiteral,
        StringLiteral,
        Identifier,
        NewLine,
        Comment
    };

    struct Token {
        TokenType type;
        utils::Slice<uint8_t> span;
    };    

    struct TokenGroup {
        std::unique_ptr<uint8_t[]> tokens;
        size_t size;
        TokenType type;
    };

    struct Grammar {
        utils::Slice<TokenGroup> tokens;
        utils::Slice<TokenGroup> delimited_tokens;
        utils::Slice<uint8_t> delimiters;
    };

    Grammar build();
}