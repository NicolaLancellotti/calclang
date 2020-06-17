set(LibHeaders ${Headers}/AST)

add_library(calclangAST STATIC
        ${LibHeaders}/AST.h
        ${LibHeaders}/NodeAST.h
        ${LibHeaders}/Expressions.h
        ${LibHeaders}/Visitor.h
        AST.cpp
)

target_include_directories(calclangAST PUBLIC
        ${LibHeaders}
        ${Headers}/ParseLex
)