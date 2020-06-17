add_executable(calclangTests
        TestLexer.cpp
        TestParser.cpp
        TestSema.cpp
        TestEvaluator.cpp
)

target_link_libraries(calclangTests PUBLIC
        gtest
        gtest_main
        calclangAST
        calclangParseLex
        calclangSema
        calclangBasic
        calclangEvaluator
)

target_include_directories(calclangTests PUBLIC
        ${Headers}/ParseLex
        ${Headers}/AST
        ${Headers}/Sema
        ${Headers}/Evaluator
        ${Headers}/Utility
)