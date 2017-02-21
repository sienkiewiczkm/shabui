%name-prefix "shabui"

%{
#include <stdio.h>
#include "shabuiAst.h"
%}

%token KEYWORD_VERSION KEYWORD_SHADER
%token KEYWORD_GEOMETRY KEYWORD_VERTEX KEYWORD_FRAGMENT
%token BRACKET_OPEN BRACKET_CLOSE
%token <intValue> NUMBER
%token STRING_LITERAL
%token IDENTIFIER
%token SEMICOLON
%token EOL

%union {
    struct shabuiAst* ast;
    int intValue;
}

%%

scriptfile: %empty
    | scriptline command_separator scriptfile
    | EOL
    ;

scriptline: version_marker;

version_marker: KEYWORD_VERSION NUMBER {
    fprintf(stderr, "found version tag: %d\n", $2);
}

command_separator: SEMICOLON | EOL;

%%


int shabuierror(char* s)
{
    fprintf(stderr, "error: %s", s);
    return 0;
}
