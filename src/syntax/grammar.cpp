#include "../utils/slice.h"
#include "../utils/array.h"

#include "tokenize.h"
#include "grammar.h"
#include "cpp.h"

using namespace utils;
using namespace syntax;

const auto default_tokens = array::from<TokenGroup>(
    tokens(cpp::Keywords, syntax::TokenType::Keyword),
    tokens(cpp::TypeKeywords, syntax::TokenType::TypeKeyword)
);

Grammar syntax::build() {
    return Grammar {
        tokens: slice::from(default_tokens),
        delimiter: cpp::Delimiter
    };
}