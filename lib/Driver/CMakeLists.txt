set(LibHeaders ${Headers}/Driver)

add_library(calclangDriver STATIC
        ${LibHeaders}/Driver.h
        Driver+run.cpp
        Driver+parse_args.cpp
)

target_include_directories(calclangDriver PUBLIC
        ${LibHeaders}
        ${Headers}/Evaluator
        ${Headers}/AST
        ${Headers}/ParseLex
        ${Headers}/Sema
        ${Headers}/Basic
        ${Headers}/ASTDump
)