#include <array>

#include "../utils/slice.h"
#include "../syntax/tokenize.h"
#include "theme.h"

using namespace utils;
using namespace syntax;
using namespace settings;

const auto syntax_styles_index() {
    return std::array<Slice<uint8_t>, 8> {
        Slice(theme::Plain.data(), theme::Plain.size()),
        Slice(theme::Operator.data(), theme::Operator.size()),
        Slice(theme::Delimiter.data(), theme::Delimiter.size()),
        Slice(theme::Keyword.data(), theme::Keyword.size()),
        Slice(theme::TypeKeyword.data(), theme::TypeKeyword.size()),
        Slice(theme::Number.data(), theme::Number.size()),
        Slice(theme::String.data(), theme::String.size()),
        Slice(theme::Comment.data(), theme::Comment.size())
    };
} 

const auto syntax_styles = syntax_styles_index();

const Slice<uint8_t> theme::syntax_style(syntax::TokenType token_type) {
    return syntax_styles[static_cast<int>(token_type)];
}