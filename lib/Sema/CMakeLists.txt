set(LibHeaders ${Headers}/Sema)

add_library(calclangSema STATIC
        ${LibHeaders}/SemanticAnalysisVisitor.h
        SemanticAnalysisVisitor.cpp
        ${LibHeaders}/SymbolTable.h
        ${LibHeaders}/DiagnosticEngine.h
)

target_include_directories(calclangSema PUBLIC
        ${LibHeaders}
        ${Headers}/AST
        ${Headers}/ParseLex
        ${Headers}/Basic
)
