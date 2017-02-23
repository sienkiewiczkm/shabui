%option c++
%option nodefault
%option noyywrap

%{
#include <stdexcept>
#include <cstdlib>
#include "shabuiParser.hxx"
#include "shabuiScanner.hpp"

#define YY_USER_ACTION yylloc->columns(yyleng);

#define YIELD_TOKEN_MARKER(tok) return sb::shabuiParser::token::T_##tok
%}

%%

%{
    yylloc->step();
%}

"version" { YIELD_TOKEN_MARKER(VERSION); }

[ \r\t]* { /* ignore whitespace */ }
\n|\r\n { yylloc->lines(1); }
. { fprintf(stderr, "Unrecognized character: %c\n", *yytext); }

%%

sb::shabuiScanner::shabuiScanner(std::istream* input, std::ostream* output):
    yyFlexLexer(input, output)
{
}

int yyFlexLexer::yylex()
{
    throw std::logic_error(
        "The yylex() exists for technical reasons and must not be used."
    );
}
