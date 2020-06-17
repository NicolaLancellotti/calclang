#include "SemanticAnalysisVisitor.h"

using namespace calclang;

auto SemanticAnalysisVisitor::visit(NumberAST& node) -> void {

}

auto SemanticAnalysisVisitor::visit(BinaryOperationAST& node) -> void {
    if (check_defined_variable(node.left_expression().get())) {
        node.left_expression()->accept(*this);
    }

    if (check_defined_variable(node.right_expression().get())) {
        node.right_expression()->accept(*this);
    }
}

auto SemanticAnalysisVisitor::visit(BlockAST& node) -> void {
    _symbols.enter_scope();
    {
        for (auto& expression : node.expressions()) {
            expression->accept(*this);
        }
    }
    _symbols.exit_scope();
}

auto SemanticAnalysisVisitor::visit(AssignAST& node) -> void {
    if (VariableAST* variable = dynamic_cast<VariableAST*>(node.variable().get())) {
        _symbols.add_variable(variable->id());
    } else {
        _diagnostic.assign_to_rvalue(node.variable()->location(), Error::AssignToRval);
    }

    if (check_defined_variable(node.expression().get())) {
        node.expression()->accept(*this);
    }
}

auto SemanticAnalysisVisitor::visit(VariableAST& node) -> void {
    check_defined_variable(&node);
}

auto SemanticAnalysisVisitor::check_defined_variable(const ExpressionAST* expression) -> bool {
    if (const VariableAST* variable = dynamic_cast<const VariableAST*>(expression)) {
        if (!_symbols.exist_variable(variable->id())) {
            _diagnostic.undefined_variable(variable->location(), variable->id());
            return false;
        }
    }
    return true;
}