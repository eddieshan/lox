#pragma once

#include <memory>

#include "../utils/slice.h"

namespace syntax {
    enum class TokenType {
        Plain,
        Keyword,
        TypeKeyword,
        NumericLiteral,
        StringLiteral,
        Identifier
    };

    struct TokenGroup {
        std::unique_ptr<uint8_t[]> tokens;
        std::unique_ptr<uint8_t[]> tokens_sizes;
        size_t n_tokens;
        TokenType type;
    };

    TokenGroup tokens(const char* tokens, const TokenType token_type);

    TokenType token_type(const utils::Slice<uint8_t>& sequence);

    bool is_delimiter(const uint8_t val);

}
