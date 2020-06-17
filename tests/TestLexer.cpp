#include <gtest/gtest.h>
#include "Shared.h"

TEST(TestLexer, punctuation) {
    const std::string source = R"(( ) { } + - * / = ;)";
    auto lexer = make_lexer(source);

    ASSERT_EQ(lexer.lex_symbol().token(), Tok::LPAR);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::RPAR);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::LCURLY);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::RCURLY);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::PLUS);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::MINUS);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::TIMES);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::DIV);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::EQUAL);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::SEMI);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::END);
}

TEST(TestLexer, numbers) {
    const std::string source = R"(0 1 12 123 004)";
    auto lexer = make_lexer(source);

    auto check = [&](int value) {
        auto symbol = lexer.lex_symbol();
        ASSERT_EQ(symbol.token(), Tok::NUMBER);
        ASSERT_EQ(symbol.value.as<int>(), value);
    };

    check(0);
    check(1);
    check(12);
    check(123);
    check(4);
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::END);
}

TEST(TestLexer, id) {
    const std::string source = R"(a a0 ab a0b ab0)";
    auto lexer = make_lexer(source);

    auto check = [&](std::string value) {
        auto symbol = lexer.lex_symbol();
        ASSERT_EQ(symbol.token(), Tok::VAR);
        ASSERT_EQ(symbol.value.as<std::string>(), value);
    };

    check("a");
    check("a0");
    check("ab");
    check("a0b");
    check("ab0");
    ASSERT_EQ(lexer.lex_symbol().token(), Tok::END);
}

TEST(TestLexer, fail) {
    const std::string source = R"(?)";;
    auto lexer = make_lexer(source);

    ASSERT_ANY_THROW(lexer.lex_symbol());
}

TEST(TestLexer, id_number) {
    const std::string source = R"(01a)";
    auto lexer = make_lexer(source);

    {
        auto symbol = lexer.lex_symbol();
        ASSERT_EQ(symbol.token(), Tok::NUMBER);
        ASSERT_EQ(symbol.value.as<int>(), 1);
    }

    {
        auto symbol = lexer.lex_symbol();
        ASSERT_EQ(symbol.token(), Tok::VAR);
        ASSERT_EQ(symbol.value.as<std::string>(), "a");
    }

    ASSERT_EQ(lexer.lex_symbol().token(), Tok::END);
}