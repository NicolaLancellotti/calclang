#include <cstdio>
#include "Lexer.h"
#include "Unreachable.h"
#include "SyntaxException.h"

using namespace calclang;

auto calclang::Lexer::lex_all() -> void {
    while(true) {
        if (lex_symbol().token() == Tok::END) {
            return;
        }
    }
}

auto calclang::Lexer::lex_symbol() -> SymbolType {
    auto token = static_cast<Tok>(_lexerFlex.yylex());
    auto location = _lexerFlex.location;
    switch (token) {
        case Tok::NUMBER: {
            errno = 0;
            int value = atoi(_lexerFlex.YYText());
            if (errno == ERANGE) {
                throw SyntaxException{location, "syntax error, integer " + std::string{_lexerFlex.YYText()} + " is out of range"};
            }
            return yy::parser::make_NUMBER(value, location);
        }
        case Tok::VAR:
            return yy::parser::make_VAR(std::string{_lexerFlex.YYText()}, location);
        default:
            return SymbolType{token, std::move(location)};
    }
}

auto calclang::Lexer::token_to_format_string(Tok token) -> const char* {
    switch (token) {
        case Tok::END: return "〈END〉";
        case Tok::PLUS: return "〈PLUS〉";
        case Tok::MINUS: return "〈MINUS〉";
        case Tok::TIMES: return "〈TIMES〉";
        case Tok::DIV: return "〈DIV〉";
        case Tok::EQUAL: return "〈EQUAL〉";
        case Tok::LPAR: return "〈LPAR〉";
        case Tok::RPAR: return "〈RPAR〉";
        case Tok::LCURLY: return "〈LCURLY〉";
        case Tok::RCURLY: return "〈RCURLY〉";
        case Tok::SEMI: return "〈SEMI〉";
        case Tok::NUMBER: return "〈NUMBER `%d`〉";
        case Tok::VAR: return "〈VAR `%s`〉";
        default: unreachable();
    }
}

auto calclang::Lexer::dump_tokens(OutputStream out_stream) -> void {
    FILE* file = out_stream.file();
    while (true) {
        auto symbol = lex_symbol();
        auto token = symbol.token();
        const char* format_string = token_to_format_string(token);

        fprintf(file, "%s ", location_to_string(symbol.location).c_str());
        switch (token) {
            case Tok::NUMBER:
                std::fprintf(file, format_string, symbol.value.as<int>()); break;
            case Tok::VAR:
                std::fprintf(file, format_string, symbol.value.as<std::string>().c_str()); break;
            default:
                fprintf(file, "%s", format_string); break;
        }
        fprintf(file, "\n");

        if (token == Tok::END) {
            break;
        }
    }
}