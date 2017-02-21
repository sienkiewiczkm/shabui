%option prefix="shabui"
%option nodefault
%option noyywrap

%{
#include <stdio.h>
#include "shabuiparser.h"
%}

%%

"version" { return KEYWORD_VERSION; }
"shader" { return KEYWORD_SHADER; }
"geometry" { return KEYWORD_GEOMETRY; }
"vertex" { return KEYWORD_VERTEX; }
"fragment" { return KEYWORD_FRAGMENT; }

"{" { return BRACKET_OPEN; }
"}" { return BRACKET_CLOSE; }
";" { return SEMICOLON; }

\"(\\.|[^\\"])*\" { return STRING_LITERAL; }
[a-zA-Z_]+[a-zA-Z_0-9]* { return IDENTIFIER; }

[0-9]+ {
    shabuilval.intValue = atoi(shabuitext);
    return NUMBER;
}

\n|\r\n { return EOL; }
[ \r\t]* { /* ignore whitespace */ }
. { fprintf(stderr, "Unrecognized character: %c\n", *shabuitext); }

