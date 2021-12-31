#pragma once

#include <memory>

namespace syntax {

    enum class TokenType: int {
        Plain = 0,
        Delimiter = 1,
        Operator = 2,
        Keyword = 3,
        TypeKeyword = 4,
        NumericLiteral = 5,
        StringLiteral = 6,
        Comment = 7
    };

    struct TokenGroup {
        std::unique_ptr<uint8_t[]> tokens;
        size_t size;
        TokenType type;

        TokenGroup(const size_t size_, TokenType type_):
            tokens(std::make_unique<uint8_t[]>(size_)),
            size(size_),
            type(type_) {
            
        };

        TokenGroup(TokenGroup&& other) noexcept:
            tokens(std::move(other.tokens)),
            size(std::move(other.size)),
            type(std::move(other.type)) {}
    };

    struct Grammar {
        utils::Slice<uint8_t> delimiters;
        utils::Slice<uint8_t> operators;
        TokenGroup keyword_delimiters;
        TokenGroup type_delimiters;
        TokenGroup string_delimiters;
        TokenGroup comment_delimiters;

        Grammar(utils::Slice<uint8_t> delimiters_,
                utils::Slice<uint8_t> operators_,
                TokenGroup keyword_delimiters_,
                TokenGroup type_delimiters_,
                TokenGroup string_delimiters_,
                TokenGroup comment_delimiters_):
            delimiters(std::move(delimiters_)),
            operators(std::move(operators_)),
            keyword_delimiters(std::move(keyword_delimiters_)),
            type_delimiters(std::move(type_delimiters_)),
            string_delimiters(std::move(string_delimiters_)),
            comment_delimiters(std::move(comment_delimiters_)) {}

        Grammar(Grammar&& other) noexcept: 
            delimiters(std::move(other.delimiters)),
            operators(std::move(other.operators)),
            keyword_delimiters(std::move(other.keyword_delimiters)),
            type_delimiters(std::move(other.type_delimiters)),
            string_delimiters(std::move(other.string_delimiters)),
            comment_delimiters(std::move(other.comment_delimiters)) {}        
    };

    Grammar build();
}