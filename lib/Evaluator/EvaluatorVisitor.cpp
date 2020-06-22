#include "Unreachable.h"
#include "EvaluatorVisitor.h"
#include "RuntimeException.h"
#include "Error.h"

using namespace calclang;

auto EvaluatorVisitor::visit(ModuleAST& node) -> void {
    node.expression()->accept(*this);
}

auto EvaluatorVisitor::visit(NumberAST& node) -> void {
    _value = node.value();
}

auto EvaluatorVisitor::visit(BinaryOperationAST& node) -> void {
    auto left_value = (node.left_expression()->accept(*this), this->_value);
    auto right_value = (node.right_expression()->accept(*this), this->_value);

    auto compute = [&](BinaryOperationAST::Operator op, int lhs, int rhs) -> int {
        using Op = BinaryOperationAST::Operator;
        switch (op) {
            case Op::Plus: return lhs + rhs;
            case Op::Minus: return lhs - rhs;
            case Op::Times: return lhs * rhs;
            case Op::DividedBy:
                return rhs != 0
                       ? lhs / rhs
                       : throw RuntimeException{node.right_expression()->location(),
                                                Error::DivisionByZero};
            default: unreachable();
        }
    };

    this->_value = compute(node.op(), left_value, right_value);
}

auto EvaluatorVisitor::visit(BlockAST& node) -> void {
    auto value = 0;
    _store.enter_scope();
    {
        for (auto& expression : node.expressions()) {
            value = (expression->accept(*this), this->_value);
        }
    }
    _store.exit_scope();
    this->_value = value;
}

auto EvaluatorVisitor::visit(AssignAST& node) -> void {
    auto value = (node.expression()->accept(*this), this->_value);

    auto variable = static_cast<VariableAST*>(node.variable().get());
    _store.set_variable_value(variable->id(), value);

    this->_value = value;
}

auto EvaluatorVisitor::visit(VariableAST& node) -> void {
    this->_value = _store.variable_value(node.id());
}