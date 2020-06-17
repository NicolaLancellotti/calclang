#include <SyntaxException.h>
#include "Parser.h"

using namespace calclang;

auto Parser::operator()() -> std::unique_ptr<RootAST> {
    std::unique_ptr<RootAST> root;

    auto x = [&]() -> SymbolType {
        return _lexer.lex_symbol();
    };

//    std::function(SymbolType<void>) p = x;

    yy::parser parser{root, _lexer};
    parser.set_debug_level(_verbose);
    parser();
    return root;
}

auto yy::parser::error(const Location& location, const std::string& text) -> void {
    throw SyntaxException{location, text};
}