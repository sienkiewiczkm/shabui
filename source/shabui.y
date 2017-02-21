%name-prefix "shabui"

%{
#include <stdio.h>
#include "shabuiAst.h"

struct shabuiAst *lastShabuiAst;
%}

%union {
    struct shabuiAst* ast;
    int intValue;
}

%token KEYWORD_VERSION KEYWORD_SHADER
%token KEYWORD_GEOMETRY KEYWORD_VERTEX KEYWORD_FRAGMENT
%token BRACKET_OPEN BRACKET_CLOSE
%token <intValue> NUMBER
%token STRING_LITERAL
%token IDENTIFIER
%token SEMICOLON
%token EOL

%start grammar_root

%type <ast> grammar_root
%type <ast> translation_unit
%type <ast> global_declaration
%type <ast> version_marker
%type <ast> shader_declaration

%%

grammar_root
    : translation_unit
    {
        lastShabuiAst = $1;
    }
    ;

translation_unit
    : global_declaration
    | translation_unit global_declaration
    {
        shabuiListAppend($1, $2);
        $$ = $1;
    }
    ;

global_declaration
    : version_marker command_separator
    | shader_declaration command_separator
    ;

version_marker
    : KEYWORD_VERSION NUMBER
    {
        $$ = shabuiMakeVersion(shabuiMakeNumber($2));
    }
    ;

shader_declaration
    : KEYWORD_SHADER shader_name shader_declaration_block
    {
        // todo: change with something with sense
        $$ = shabuiMakeNumber(6);
    }
    ;

shader_name
    : IDENTIFIER
    | STRING_LITERAL
    ;

shader_declaration_block
    : BRACKET_OPEN BRACKET_CLOSE
    ;

command_separator
    : SEMICOLON
    | EOL
    ;

%%


int shabuierror(char* s)
{
    fprintf(stderr, "error: %s", s);
    return 0;
}
