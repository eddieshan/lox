#include <memory>
#include <cstring>

#include "../utils/slice.h"
#include "../utils/array.h"
#include "tokenize.h"
#include "cpp.h"

using namespace utils;
using namespace syntax;

TokenGroup syntax::tokens(const char* tokens, const TokenType token_type) {
    size_t tokens_length = 0, n_tokens = 1;

    while(tokens[tokens_length] != '\0') {
        if(tokens[tokens_length] == '|') {
            ++n_tokens;
        }
        ++tokens_length;
    }

    const auto size = tokens_length - n_tokens - 1;

    auto token_group = TokenGroup {
        tokens: std::make_unique<uint8_t[]>(size),
        tokens_sizes: std::make_unique<uint8_t[]>(n_tokens),
        n_tokens: n_tokens,
        type: token_type
    };

    auto indices = token_group.tokens_sizes.get();
    auto token_start = token_group.tokens.get();

    auto segment_index = 0, last_index = 0;

    for(auto i = 0; i <= tokens_length; ++i) {
        if(tokens[i] == '|' || tokens[i] == '\0') {
            const auto offset = last_index == 0? last_index : last_index + 1;
            const auto token_size = i - offset;

            std::copy(tokens + offset, tokens + i, token_start);
            token_start += token_size;

            indices[segment_index] = token_size;
            last_index = i;

            ++segment_index;
        }
    }

    return token_group;
}

TokenType syntax::token_type(const Slice<uint8_t>& sequence) {

    for(auto i = 0; i < cpp::Grammar.size(); ++i) {
        const auto token_group = &cpp::Grammar[i];
        auto token_start = token_group->tokens.get();
        const auto tokens_sizes = token_group->tokens_sizes.get();

        for(auto j = 0; j < token_group->n_tokens; ++j) {

            const auto token_size = tokens_sizes[j];

            if(token_size == sequence.size) {
                if(std::memcmp(token_start, sequence.data, token_size) == 0) {
                    return token_group->type;
                }
            }

            token_start += token_size;
        }
    }

    return TokenType::Plain;
}

bool syntax::is_delimiter(const uint8_t val) {
    return val == cpp::Delimiter;
}