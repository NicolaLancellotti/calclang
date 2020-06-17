#include <gtest/gtest.h>
#include "Shared.h"

using namespace calclang;

TEST(TestParser, success) {
    const std::string source = R"(
    x = 10;
    y = {
        z = 2;
        z
    };
    y
    )";
    auto parser = make_parser(source);
    parser();
}

TEST(TestParser, fail) {
    const std::string source = R"(
    x == 10;
    y = {
        z == 2;
        z
    };
    y
    )";
    auto parser = make_parser(source);

    ASSERT_ANY_THROW(parser());
}