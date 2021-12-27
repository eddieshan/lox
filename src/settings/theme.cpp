#include "../utils/slice.h"
#include "../syntax/tokenize.h"
#include "theme.h"

using namespace utils;
using namespace syntax;
using namespace settings;

const Slice<uint8_t> theme::syntax_style(syntax::TokenType token_type) {
    if(token_type == TokenType::Keyword) {
        return Slice(theme::Keyword.data(), theme::Keyword.size());
    } else if(token_type == TokenType::TypeKeyword) {
        return Slice(theme::TypeKeyword.data(), theme::TypeKeyword.size());
    } else if(token_type == TokenType::NumericLiteral) {
        return Slice(theme::Number.data(), theme::Number.size());
    } else if(token_type == TokenType::StringLiteral) {
        return Slice(theme::String.data(), theme::String.size());
    } else {
        return Slice(theme::Plain.data(), theme::Plain.size());
    }
}