#ifndef COMPILER_EXPRESSIONS_H
#define COMPILER_EXPRESSIONS_H

#include "NodeAST.h"

namespace calclang {

    class ExpressionAST : public NodeAST {
    public:
        explicit ExpressionAST(Location location) : NodeAST{location} {};

        ACCEPT_VIRTUAL();
    };


    class NumberAST : public ExpressionAST {
    public:
        explicit NumberAST(Location location,
                           int value) :
                ExpressionAST{location},
                _value{value} {};

        auto value() const -> int const {
            return _value;
        }

        ACCEPT();

    private:
        int _value;
    };


    class BinaryOperationAST : public ExpressionAST {
    public:
        enum class Operator {
            Plus, DividedBy, Minus, Times
        };

        BinaryOperationAST(Location location,
                           std::unique_ptr<ExpressionAST> left_expression,
                           std::unique_ptr<ExpressionAST> right_expression,
                           BinaryOperationAST::Operator op) :
                ExpressionAST{location},
                _left_expression{std::move(left_expression)},
                _right_expression{std::move(right_expression)},
                _operator{std::move(op)} {};

        auto left_expression() const -> const std::unique_ptr<ExpressionAST>& {
            return _left_expression;
        }

        auto
        right_expression() const -> const std::unique_ptr<ExpressionAST>& {
            return _right_expression;
        }

        auto op() const -> BinaryOperationAST::Operator {
            return _operator;
        }

        auto op_to_string() const -> const char* {
            switch (_operator) {
                case Operator::Plus:
                    return "Plus";
                case Operator::DividedBy:
                    return "DividedBy";
                case Operator::Minus:
                    return "Minus";
                case Operator::Times:
                    return "TimesTODO";
            }
        }

        ACCEPT();

    private:
        std::unique_ptr<ExpressionAST> _left_expression;
        std::unique_ptr<ExpressionAST> _right_expression;
        BinaryOperationAST::Operator _operator;
    };


    class BlockAST : public ExpressionAST {
    public:
        BlockAST(Location location,
                 std::list<std::unique_ptr<ExpressionAST>> expressions) :
                ExpressionAST{location},
                _expressions{std::move(expressions)} {};

        auto
        expressions() const -> const std::list<std::unique_ptr<ExpressionAST>>& {
            return _expressions;
        }

        ACCEPT();
    private:
        std::list<std::unique_ptr<ExpressionAST>> _expressions;
    };


    class VariableAST : public ExpressionAST {
    public:
        VariableAST(Location location,
                    std::string id) :
                ExpressionAST{location},
                _id{id} {};

        auto id() const -> const std::string& {
            return _id;
        }

        ACCEPT();
    private:
        std::string _id;
    };


    class AssignAST : public ExpressionAST {
    public:
        explicit AssignAST(Location location,
                           std::unique_ptr<ExpressionAST> variable,
                           std::unique_ptr<ExpressionAST> expression) :
                ExpressionAST{location},
                _variable{std::move(variable)},
                _expression{std::move(expression)} {};

        auto expression() const -> const std::unique_ptr<ExpressionAST>& {
            return _expression;
        }

        auto variable() const -> const std::unique_ptr<ExpressionAST>& {
            return _variable;
        }

        ACCEPT();
    private:
        std::unique_ptr<ExpressionAST> _variable;
        std::unique_ptr<ExpressionAST> _expression;
    };

}

#endif