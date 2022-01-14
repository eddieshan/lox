#include <memory>
#include <cstring>

#include "../utils/slice.h"
#include "../utils/range.h"
#include "../utils/packed_array.h"
#include "grammar.h"
#include "cpp.h"

using namespace utils;
using namespace syntax;

constexpr auto TokenDelimiter = '|';

PackedArray tokens(const char* tokens_def, const TokenType token_type) {
    const auto tokens_length = strlen(tokens_def) + 1;
    const auto tokens = (uint8_t*)tokens_def;

    auto token_group = PackedArray(tokens_length);
    auto index = 0;

    for(auto i = 0; i < tokens_length; ++i) {
        if(tokens_def[i] == TokenDelimiter || tokens_def[i] == '\0') {
            const auto offset = index == 0? index : index + 1;
            token_group.append(tokens + offset, tokens + i);
            index = i;
        }
    }

    return token_group;
}

Grammar syntax::build() {
    return Grammar(
        slice::from(cpp::Delimiters),
        cpp::FunctionCallDelimiters,
        slice::from(cpp::Operators),
        tokens(cpp::Keywords, syntax::TokenType::Keyword),
        tokens(cpp::TypeKeywords, syntax::TokenType::TypeKeyword),
        tokens(cpp::StringDelimiters, syntax::TokenType::StringLiteral),
        tokens(cpp::CommentDelimiters, syntax::TokenType::Comment)
    );
}