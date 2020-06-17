#include <gtest/gtest.h>
#include "Shared.h"
#include "SemanticAnalysisVisitor.h"
#include "EvaluatorVisitor.h"

using namespace calclang;

TEST(TestEvaluator, success) {
    const std::string source = R"(
    x = 10;
    y = {
        x = x * 20;
        x = x / 2;
        x = x + 50;
        x = x - 100;
        x
    };
    y = y - 10;
    y = { y };
    y = {
        x = 1;
        y
    }
    )";
    auto root_node = make_parser(source)();
    SemanticAnalysisVisitor{true}(root_node);

    auto evaluator = EvaluatorVisitor{};
    ASSERT_EQ(evaluator(root_node), 40);
}