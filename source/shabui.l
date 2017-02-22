%option prefix="shabui"
%option nodefault
%option noyywrap

%{
#include <stdio.h>
#include "shabuiparser.h"
#include "shabuiAst.h"
%}

%%

"version" { return KEYWORD_VERSION; }
"shader" { return KEYWORD_SHADER; }
"geometry" { return KEYWORD_GEOMETRY; }
"vertex" { return KEYWORD_VERTEX; }
"fragment" { return KEYWORD_FRAGMENT; }

"(" { return PARENTHESIS_OPEN; }
")" { return PARENTHESIS_CLOSE; }
"{" { return BRACKET_OPEN; }
"}" { return BRACKET_CLOSE; }
":" { return COLON; }
";" { return SEMICOLON; }
"=" { return ASSIGNMENT; }

\<\<\<([^\>\>\>]|\n|\r\n)*\>\>\> {
    shabuilval.ast = shabuiMakeString(shabuitext);
    return GLSL_BLOCK;
}

\"(\\.|[^\\"])*\" {
    shabuilval.ast = shabuiMakeString(shabuitext);
    return STRING_LITERAL;
}

[a-zA-Z_]+[a-zA-Z_0-9]* {
    shabuilval.ast = shabuiMakeString(shabuitext);
    return IDENTIFIER;
}

[0-9]+ {
    shabuilval.intValue = atoi(shabuitext);
    return NUMBER;
}

\n|\r\n|\r { /* ignore linebreaks */ }
[ \r\t]* { /* ignore whitespace */ }

. { fprintf(stderr, "Unrecognized character: %c\n", *shabuitext); }
