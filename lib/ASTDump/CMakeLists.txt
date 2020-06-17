set(LibHeaders ${Headers}/ASTDump)

add_library(calclangASTDump STATIC
        ${LibHeaders}/tinyxml2.h
        tinyxml2.cpp
        ${LibHeaders}/AST2XMLVisitor.h
        AST2XMLVisitor.cpp
)

target_include_directories(calclangASTDump PUBLIC
        ${LibHeaders}
        ${Headers}/ParseLex
        ${Headers}/AST
        ${Headers}/Basic
)