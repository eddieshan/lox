#include <array>

#include "../utils/slice.h"
#include "../syntax/tokenize.h"
#include "theme.h"

using namespace utils;
using namespace syntax;
using namespace settings;

const auto syntax_styles_index() {
    return std::array<std::array<uint8_t, 9>, 8> {
        theme::Plain,
        theme::Operator,
        theme::Delimiter,
        theme::Keyword,
        theme::TypeKeyword,
        theme::Number,
        theme::String,
        theme::Comment
    };
} 

const auto syntax_styles = syntax_styles_index();

const std::array<uint8_t, 9> theme::syntax_style(syntax::TokenType token_type) {
    return syntax_styles[static_cast<int>(token_type)];
}