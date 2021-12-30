#include <memory>
#include <cstring>

#include "../utils/slice.h"
#include "grammar.h"
#include "cpp.h"

using namespace utils;
using namespace syntax;

constexpr auto TokenDelimiter = '|';

TokenGroup tokens(const char* tokens_def, const TokenType token_type) {

    const auto tokens_length = strlen(tokens_def) + 1;

    auto token_group = TokenGroup {
        tokens: std::make_unique<uint8_t[]>(tokens_length),
        size: tokens_length,
        type: token_type
    };

    const auto tokens = token_group.tokens.get();
    auto index = 0;

    for(auto i = 0; i < tokens_length; ++i) {
        if(tokens_def[i] == TokenDelimiter || tokens_def[i] == '\0') {
            const auto offset = index == 0? index : index + 1;
            const auto token_size = i - offset;

            tokens[offset] = token_size;
            std::copy(tokens_def + offset, tokens_def + i, tokens + offset + 1);

            index = i;
        }
    }

    return token_group;
}

const auto fixed_tokens = std::array<TokenGroup, 3> {
    tokens(cpp::Keywords, syntax::TokenType::Keyword),
    tokens(cpp::TypeKeywords, syntax::TokenType::TypeKeyword),
    tokens(cpp::Operators, syntax::TokenType::Operator)    
};

const auto delimited_tokens = std::array<TokenGroup, 2> {
    tokens(cpp::StringDelimiters, syntax::TokenType::StringLiteral),
    tokens(cpp::CommentDelimiters, syntax::TokenType::Comment)
};

Grammar syntax::build() {
    return Grammar {
        fixed_tokens: Slice(fixed_tokens.data(), fixed_tokens.size()),
        delimited_tokens: Slice(delimited_tokens.data(), delimited_tokens.size()),
        delimiters: slice::from(cpp::Delimiters)
    };
}