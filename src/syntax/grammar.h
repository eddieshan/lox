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
        Comment = 7,
        NewLine = 8
    };

    // namespace TokenType {
    //     enum TokenType {
    //         Plain,
    //         Delimiter,
    //         Operator,
    //         Keyword,
    //         TypeKeyword,
    //         NumericLiteral,
    //         StringLiteral,
    //         Comment,
    //         NewLine
    //     };
    // }


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
        utils::Slice<TokenGroup> fixed_tokens;
        utils::Slice<TokenGroup> delimited_tokens;
        utils::Slice<uint8_t> delimiters;
    };

    Grammar build();
}