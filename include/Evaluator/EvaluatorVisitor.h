#ifndef COMPILER_EVALUATORVISITOR_H
#define COMPILER_EVALUATORVISITOR_H

#include "Visitor.h"
#include "Store.h"
#include "AST.h"

namespace calclang {

    class EvaluatorVisitor : public Visitor {
    public:

        auto operator()(std::unique_ptr<RootAST>& node) -> int {
            node->accept(*this);
            return this->_value;
        }

        auto visit(NumberAST&) -> void override;

        auto visit(BinaryOperationAST&) -> void override;

        auto visit(BlockAST&) -> void override;

        auto visit(AssignAST&) -> void override;

        auto visit(VariableAST&) -> void override;

    private:
        int _value{0};
        StoreManager _store{};
    };

}

#endif