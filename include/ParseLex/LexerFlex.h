#ifndef COMPILER_LEXER_FLEX_H
#define COMPILER_LEXER_FLEX_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "Location.h"
#include "Bison.h"
#include "SyntaxException.h"

namespace calclang {

    class LexerFlex : public yyFlexLexer {
    public:
        using yyFlexLexer::yyFlexLexer;

        LexerFlex(std::istream* arg_yyin,
                  std::ostream* arg_yyout,
                  std::string* fileName,
                  bool debug) :
                yyFlexLexer{arg_yyin, arg_yyout} {
            set_debug(debug);
            location.initialize(fileName);
        }

        auto yylex() -> int override;

        auto yywrap() -> int override {
            return 1;
        }

        calclang::Location location;
    };

}

#endif