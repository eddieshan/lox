#include <memory>
#include <cstring>

#include "../utils/slice.h"
#include "../utils/array.h"
#include "tokenize.h"
#include "cpp.h"

using namespace utils;
using namespace syntax;

constexpr auto TokenDelimiter = '|';

TokenGroup syntax::tokens(const char* tokens_def, const TokenType token_type) {

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

const auto Grammar = utils::array::from<TokenGroup>(
    syntax::tokens(cpp::Keywords, syntax::TokenType::Keyword),
    syntax::tokens(cpp::TypeKeywords, syntax::TokenType::TypeKeyword)
);

TokenType syntax::token_type(const Slice<uint8_t>& sequence) {

    for(auto i = 0; i < Grammar.size(); ++i) {
        const auto tokens = Grammar[i].tokens.get();

        size_t length_index = 0;

        while(length_index < Grammar[i].size) {
            const auto token_size = tokens[length_index];
            const auto token_index = length_index + 1;

            if(token_size == sequence.size) {
                if(std::memcmp(tokens + token_index, sequence.data, token_size) == 0) {
                    return Grammar[i].type;
                }
            }

            length_index += (token_size + 1);
        }
    }

    return TokenType::Plain;
}

bool syntax::is_delimiter(const uint8_t val) {
    return val == cpp::Delimiter;
}