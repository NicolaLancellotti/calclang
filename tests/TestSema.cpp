#include <gtest/gtest.h>
#include "Shared.h"
#include "SemanticAnalysisVisitor.h"

using namespace calclang;

TEST(TestSema, success) {
    const std::string source = R"(
    x = 10;
    y = {
        z = 2;
        z
    };
    y
    )";
    auto root_node = make_parser(source)();
    auto semantic_analyser = SemanticAnalysisVisitor{true};

    ASSERT_TRUE(semantic_analyser(root_node));
}


TEST(TestSema, undefined_variable_1) {
    const std::string source = R"(
    y = {
        z = undefined
    }
    )";
    auto root_node = make_parser(source)();
    auto semantic_analyser = SemanticAnalysisVisitor{false};

    ASSERT_FALSE(semantic_analyser(root_node));
}

TEST(TestSema, undefined_variable_2) {
    const std::string source = R"(
    x = 10;
    y = {
        z = undefined  + x
    }
    )";
    auto root_node = make_parser(source)();
    auto semantic_analyser = SemanticAnalysisVisitor{false};

    ASSERT_FALSE(semantic_analyser(root_node));
}

TEST(TestSema, undefined_variable_3) {
    const std::string source = R"(
    x = 10;
    y = {
        z = x * undefined
    }
    )";
    auto root_node = make_parser(source)();
    auto semantic_analyser = SemanticAnalysisVisitor{false};

    ASSERT_FALSE(semantic_analyser(root_node));
}

TEST(TestSema, assign_to_rvalue) {
    const std::string source = R"(
    y = {
        2 + 2 = 2
    }
    )";
    auto root_node = make_parser(source)();
    auto semantic_analyser = SemanticAnalysisVisitor{false};

    ASSERT_FALSE(semantic_analyser(root_node));
}