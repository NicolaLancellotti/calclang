#ifndef COMPILER_BISON_H
#define COMPILER_BISON_H

namespace calclang {
    class Lexer;
    class LexerFlex;
}

#include "AST.h"
#include "BisonGen.h"

namespace  calclang {
    using SymbolType = yy::parser::symbol_type;
    using Tok = yy::parser::token::yytokentype;
}

#endif