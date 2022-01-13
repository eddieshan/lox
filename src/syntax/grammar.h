#pragma once

#include <memory>

#include "../utils/slice.h"
#include "../utils/range.h"
#include "../utils/packed_array.h"

namespace syntax {

    enum class TokenType: int {
        Plain = 0,
        Delimiter = 1,
        Operator = 2,
        Keyword = 3,
        TypeKeyword = 4,
        NumericLiteral = 5,
        StringLiteral = 6,
        Comment = 7,
        Function = 8
    };

    struct Grammar {
        utils::Slice<uint8_t> delimiters;
        utils::Range<uint8_t> function_call_delimiters;
        utils::Slice<uint8_t> operators;
        utils::PackedArray keyword_delimiters;
        utils::PackedArray type_delimiters;
        utils::PackedArray string_delimiters;
        utils::PackedArray comment_delimiters;

        Grammar(utils::Slice<uint8_t> delimiters_,
                utils::Range<uint8_t> function_call_delimiters_,
                utils::Slice<uint8_t> operators_,
                utils::PackedArray keyword_delimiters_,
                utils::PackedArray type_delimiters_,
                utils::PackedArray string_delimiters_,
                utils::PackedArray comment_delimiters_):
            delimiters(delimiters_),
            function_call_delimiters(function_call_delimiters_),
            operators(operators_),
            keyword_delimiters(std::move(keyword_delimiters_)),
            type_delimiters(std::move(type_delimiters_)),
            string_delimiters(std::move(string_delimiters_)),
            comment_delimiters(std::move(comment_delimiters_)) {}

        Grammar(Grammar&& other) noexcept: 
            delimiters(other.delimiters),
            function_call_delimiters(other.function_call_delimiters),
            operators(other.operators),
            keyword_delimiters(std::move(other.keyword_delimiters)),
            type_delimiters(std::move(other.type_delimiters)),
            string_delimiters(std::move(other.string_delimiters)),
            comment_delimiters(std::move(other.comment_delimiters)) {}
    };

    Grammar build();
}