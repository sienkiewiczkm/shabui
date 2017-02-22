%name-prefix "shabui"
%define parse.error verbose

%{
#include <stdio.h>
#include "shabuiAst.h"

struct shabuiAst *lastShabuiAst;
%}

%union {
    struct shabuiAst* ast;
    int intValue;
}

%token KEYWORD_VERSION
%token KEYWORD_SHADER
%token KEYWORD_GEOMETRY
%token KEYWORD_VERTEX
%token KEYWORD_FRAGMENT
%token PARENTHESIS_OPEN
%token PARENTHESIS_CLOSE
%token BRACKET_OPEN
%token BRACKET_CLOSE
%token COLON SEMICOLON ASSIGNMENT
%token EOL
%token END_OF_FILE

%token <intValue> NUMBER
%token <ast> IDENTIFIER
%token <ast> STRING_LITERAL
%token <ast> GLSL_BLOCK

%type <ast> root
%type <ast> translation_unit
%type <ast> global_declaration
%type <ast> version_marker
%type <ast> shader_declaration
%type <ast> shader_declaration_block
%type <ast> shader_properties
%type <ast> shader_property
%type <ast> shader_name

%start root

%%

root
    : translation_unit
    {
        lastShabuiAst = $1;
    }
    ;

translation_unit
    : global_declaration command_separator
    | translation_unit global_declaration command_separator
    {
        shabuiListAppend($1, $2);
        $$ = $1;
    }
    ;

global_declaration
    : version_marker
    | shader_declaration
    ;

version_marker
    : KEYWORD_VERSION NUMBER
    {
        $$ = shabuiMakeVersion($2);
    }
    ;

shader_declaration
    : KEYWORD_SHADER shader_name shader_declaration_block
    {
        $$ = shabuiMakeShader($2, $3);
    }
    ;

shader_name
    : IDENTIFIER
    | STRING_LITERAL
    ;

shader_declaration_block
    : BRACKET_OPEN BRACKET_CLOSE
    | BRACKET_OPEN shader_properties BRACKET_CLOSE { $$ = $2; }
    ;

shader_properties
    : shader_property command_separator
    | shader_properties shader_property command_separator
    {
        shabuiListAppend($1, $2);
        $$ = $1;
    }
    ;

shader_property
    : shader_program_property shader_program_inputs ASSIGNMENT GLSL_BLOCK
    {
        $$ = $4;
    }
    ;

shader_program_inputs
    : PARENTHESIS_OPEN PARENTHESIS_CLOSE

shader_program_property
    : KEYWORD_VERTEX
    | KEYWORD_FRAGMENT
    ;

command_separator
    : SEMICOLON
    ;

%%


int shabuierror(char* s)
{
    fprintf(stderr, "error: %s", s);
    return 0;
}
