set(LibHeaders ${Headers}/Evaluator)

add_library(calclangEvaluator STATIC
        ${LibHeaders}/EvaluatorVisitor.h
        EvaluatorVisitor.cpp
        ${LibHeaders}/Store.h
        ${LibHeaders}/RuntimeException.h
)

target_include_directories(calclangEvaluator PUBLIC
        ${LibHeaders}
        ${Headers}/AST
        ${Headers}/ParseLex
        ${Headers}/Basic
)
