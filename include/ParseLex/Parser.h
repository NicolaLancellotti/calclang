#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <memory>
#include "AST.h"
#include "Lexer.h"

namespace calclang {

    class Parser {
    public:
        Parser(const Parser&) = delete;
        Parser &operator=(const Parser&) = delete;
        Parser(Parser&&) = default;
        Parser &operator=(Parser&&) = default;

        Parser(Lexer lexer, bool verbose) : _lexer{std::move(lexer)},
                                            _verbose{verbose} {};

        auto operator()() -> std::unique_ptr<RootAST>;

    private:
        Lexer _lexer;
        bool _verbose;
    };

}

#endif
