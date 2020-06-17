set(LibHeaders ${Headers}/ParseLex)
set(ThisDirectory  ${CMAKE_SOURCE_DIR}/lib/ParseLex)

find_package(FLEX)
find_package(BISON)

flex_target(calclangLexerFlex
        flex.l
        ${CMAKE_CURRENT_BINARY_DIR}/FlexGen.cpp
)

bison_target(calclangParserBison bison.y++
        ${ThisDirectory}/BisonGen.cpp
        DEFINES_FILE ${LibHeaders}/BisonGen.h
        VERBOSE
        COMPILE_FLAGS --report=itemset
        COMPILE_FLAGS --report=lookahead
        COMPILE_FLAGS --report=solved)

add_flex_bison_dependency(calclangLexerFlex calclangParserBison)

add_library(calclangParseLex STATIC
        ${LibHeaders}/Lexer.h
        Lexer.cpp

        ${LibHeaders}/LexerFlex.h

        ${LibHeaders}/Parser.h
        Parser.cpp

        ${CMAKE_CURRENT_BINARY_DIR}/FlexGen.cpp
        ${LibHeaders}/BisonGen.h
        ${ThisDirectory}/BisonGen.cpp
        ${ThisDirectory}/BisonGen.output

        ${LibHeaders}/Bison.h
        ${LibHeaders}/Location.h
        ${LibHeaders}/location.hh

        ${LibHeaders}/SyntaxException.h
)

target_include_directories(calclangParseLex PUBLIC
        ${LibHeaders}
        ${Headers}/AST
        ${Headers}/Basic
)

#add_dependencies(calclangParseLex calclangLexerFlex calclangParserBison)
