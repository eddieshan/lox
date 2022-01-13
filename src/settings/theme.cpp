#include <array>

#include "../utils/slice.h"
#include "../term/ansi.h"
#include "../syntax/tokenize.h"
#include "theme.h"

using namespace utils;
using namespace term::ansi;
using namespace syntax;
using namespace settings;

const auto syntax_styles = std::array {
    theme::syntax_highlight::Plain,
    theme::syntax_highlight::Operator,
    theme::syntax_highlight::Delimiter,
    theme::syntax_highlight::Keyword,
    theme::syntax_highlight::TypeKeyword,
    theme::syntax_highlight::Number,
    theme::syntax_highlight::String,
    theme::syntax_highlight::Comment,
    theme::syntax_highlight::Function    
};

const ColorAttribute theme::syntax_style(syntax::TokenType token_type) {
    return syntax_styles[static_cast<int>(token_type)];
}