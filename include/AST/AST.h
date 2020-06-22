#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#include "Expressions.h"

namespace calclang {

    class ModuleAST : public NodeAST {
    public:
        explicit ModuleAST(Location location,
                           std::unique_ptr<ExpressionAST> expression) :
                NodeAST{location},
                _expression{std::move(expression)} {};

        ACCEPT();

        auto expression() const -> const std::unique_ptr<ExpressionAST>& {
            return _expression;
        }

    private:
        std::unique_ptr<ExpressionAST> _expression;
    };

}



#endif
