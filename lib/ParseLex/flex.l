%{
    #define register
    #include "LexerFlex.h"

    //#define YY_DECL int calclang::LexerFlex::yylex()
    #define YY_USER_ACTION  {location.columns (yyleng);}
%}

%option c++
%option yyclass="calclang::LexerFlex"
/* Default yyFlexLexer::yywrap() */
%option noyywrap
/* Allow debug */
%option debug

letter  [A-Za-z]
digit   [0-9]
int     {digit}*
id      {letter}({letter}|{digit})*

%%

"\n"              location.lines(1); location.step();
[ \t]             location.step();

"("               return Tok::LPAR;
")"               return Tok::RPAR;
"{"               return Tok::LCURLY;
"}"               return Tok::RCURLY;

"+"               return Tok::PLUS;
"-"               return Tok::MINUS;
"*"               return Tok::TIMES;
"/"           	  return Tok::DIV;
"="           	  return Tok::EQUAL;

";"           	  return Tok::SEMI;
{int}             return Tok::NUMBER;
{id}              return Tok::VAR;

.                 throw SyntaxException{location, "syntax error, unexpected `" + std::string(yytext) + "`"};
<<EOF>>           return Tok::END;

%%


