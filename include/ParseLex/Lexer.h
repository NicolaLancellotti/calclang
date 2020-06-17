#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include "LexerFlex.h"
#include <fstream>
#include "OutputStream.h"
#include "InputStream.h"

namespace calclang {

    class Lexer {
    public:
        Lexer(const Lexer&) = delete;
        Lexer& operator=(const Lexer&) = delete;
        Lexer(Lexer&&) = default;
        Lexer& operator=(Lexer&&) = default;

        Lexer(InputStream in_stream, bool verbose): _in_stream{std::move(in_stream)} {
            if (auto name = this->_in_stream.name()) {
                _file_name = std::make_unique<std::string>(*name);
            }
            _lexerFlex = LexerFlex{this->_in_stream.stream(),
                                   nullptr,
                                   _file_name.get(),
                                   verbose};
        }

        auto dump_tokens(OutputStream out_stream) -> void;

        auto lex_symbol() -> SymbolType;

        auto lex_all() -> void;

    private:
        inline auto token_to_format_string(Tok token) -> const char*;
        InputStream _in_stream{};
        std::unique_ptr<std::string> _file_name = nullptr;
        LexerFlex _lexerFlex;
    };

}

#endif
