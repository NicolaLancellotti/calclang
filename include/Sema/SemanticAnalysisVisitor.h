#ifndef COMPILER_SEMANTICANALYSISVISITOR_H
#define COMPILER_SEMANTICANALYSISVISITOR_H

#include "Visitor.h"
#include "AST.h"
#include "SymbolTable.h"
#include "DiagnosticEngine.h"

namespace calclang {

    class SemanticAnalysisVisitor : public Visitor {
    public:
        SemanticAnalysisVisitor(bool show_error): _diagnostic{show_error} {};

        auto operator()(std::unique_ptr<ModuleAST>& Node) -> bool {
            Node->accept(*this);
            return _diagnostic.is_correct();
        }

        auto visit(ModuleAST&) -> void override;

        auto visit(NumberAST&) -> void override;

        auto visit(BinaryOperationAST&) -> void override;

        auto visit(BlockAST&) -> void override;

        auto visit(AssignAST&) -> void override;

        auto visit(VariableAST&) -> void override;

    private:
        auto check_defined_variable(const ExpressionAST* expression) -> bool;

        SymbolTableManager _symbols{};
        DiagnosticEngine _diagnostic;
    };

}

#endif