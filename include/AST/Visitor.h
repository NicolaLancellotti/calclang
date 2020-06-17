#ifndef COMPILER_VISITOR_H
#define COMPILER_VISITOR_H

namespace calclang {

    class NumberAST;

    class BinaryOperationAST;

    class BlockAST;

    class AssignAST;

    class VariableAST;

    class Visitor {
    public:
        virtual auto visit(NumberAST&) -> void = 0;

        virtual auto visit(BinaryOperationAST&) -> void = 0;

        virtual auto visit(BlockAST&) -> void = 0;

        virtual auto visit(AssignAST&) -> void = 0;

        virtual auto visit(VariableAST&) -> void = 0;
    };

}

#endif