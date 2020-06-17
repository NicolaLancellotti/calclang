#ifndef COMPILER_SHARED_H
#define COMPILER_SHARED_H

#include "Lexer.h"
#include "Parser.h"
#include "InputStream.h"

using namespace calclang;

inline auto make_lexer(const std::string& source) -> Lexer {
    return Lexer{ InputStream{source}, false};
}

inline auto make_parser(const std::string& source) -> Parser {
    return Parser{make_lexer(source), false};
}

#endif
