%option c++
%option nodefault
%option noyywrap

%{
#include <stdexcept>
#include <cstdlib>
#include "shabuiParser.hxx"
#include "shabuiScanner.hpp"
#include "stringUtils.hpp"

#if __cplusplus > 199711L
#define register // Deprecated in C++11.
#endif// __cplusplus > 199711L

#define YY_USER_ACTION yylloc->columns(yyleng);
#define YY_STRING std::string(yytext, yyleng)

#define YIELD_TOKEN(tok, val, type) \
    yylval->build<type>(val); \
    return sb::shabuiParser::token::T_##tok

#define YIELD_TOKEN_MARKER(tok) return sb::shabuiParser::token::T_##tok
#define YIELD_STRING(tok) YIELD_TOKEN(tok, YY_STRING, std::string);
%}

%%

%{
    yylloc->step();
%}

"version" { YIELD_TOKEN_MARKER(VERSION); }
"shader"  { YIELD_TOKEN_MARKER(SHADER); }
"shared"  { YIELD_TOKEN_MARKER(SHARED); }
"func"    { YIELD_TOKEN_MARKER(FUNC); }
"glsl"    { YIELD_TOKEN_MARKER(GLSL); }

"void"                   { YIELD_STRING(GLSL_TYPE); }
"bool"                   { YIELD_STRING(GLSL_TYPE); }
"float"                  { YIELD_STRING(GLSL_TYPE); }
"double"                 { YIELD_STRING(GLSL_TYPE); }
[u]?"int"                { YIELD_STRING(GLSL_TYPE); }
[d]?"mat"[2-4]("x"[2-4]) { YIELD_STRING(GLSL_TYPE); }
[dbiu]?"vec"[2-4]        { YIELD_STRING(GLSL_TYPE); }

\"(\\.|[^\\"])*\" {
    auto text = stripKnownEndings(YY_STRING, "\"", "\"");
    YIELD_TOKEN(STRING_LITERAL, text, std::string);
}

\<\<\<([^\>\>\>]|\n|\r\n)*\>\>\> {
    auto text = stripKnownEndings(YY_STRING, "<<<", ">>>");
    YIELD_TOKEN(GLSL_CODE_BLOCK, text, std::string);
}

[0-9]+ {
    int value = std::stoi(YY_STRING);
    YIELD_TOKEN(INTEGER_CONSTANT, value, int);
}

[_a-zA-Z]+[_a-zA-Z0-9]* { YIELD_STRING(IDENTIFIER); }

[ \r\t]* { /* ignore whitespace */ }
\n|\r\n { yylloc->lines(1); }
. { return yytext[0]; }

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
