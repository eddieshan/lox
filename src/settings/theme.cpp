#include "../utils/array.h"
#include "../syntax/tokenize.h"
#include "theme.h"

using namespace syntax;
using namespace settings;

const std::array<uint8_t, 11>& theme::syntax_style(syntax::TokenType token_type) {
    if(token_type == TokenType::Keyword) {
        return theme::Keyword;
    } else if(token_type == TokenType::TypeKeyword) {
        return theme::TypeKeyword;
    } else if(token_type == TokenType::NumericLiteral) {
        return theme::Number;
    } else if(token_type == TokenType::StringLiteral) {
        return theme::String;
    } else {
        return theme::Plain;
    }
}