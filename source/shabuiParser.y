%skeleton "lalr1.cc"
%require "3.0"
%parse-param {sb::shabuiScanner* scanner} {sb::ParserOutput* cb}
%locations
%define parser_class_name {shabuiParser}
%define parse.error verbose
%define parse.assert
%define api.namespace {sb}
%define api.value.type variant
%define api.token.prefix {T_}

%code requires {
    #include <stdexcept>
    #include <string>
    #include "shabuiAst.hpp"
    #include "parserOutput.hpp"
    #include "location.hh"

    namespace sb
    {
        class shabuiScanner;
    }
}

%code {
    #include <iostream>
    #include <utility>
    #include <string>
    #include <sstream>
    #include "shabuiScanner.hpp"
    #undef yylex
    #define yylex scanner->lex

    template <class T, class V>
    T&& enlist(T& t, V& v)
    {
        t.push_back(std::move(v));
        return std::move(t);
    }
}

%token END 0 "end of file"

%token <std::string> IDENTIFIER
%token <std::string> STRING_LITERAL
%token <std::string> GLSL_CODE_BLOCK
%token <std::string> GLSL_TYPE

%token VERSION SHADER FUNC SHARED GLSL STRUCT
%token COLON

%token <int> INTEGER_CONSTANT

%type <std::string> shader_name
%type <std::string> shader_shared_code_property

%type <ShaderDefinition> shader_definition shader_properties_list

%type <FunctionDefinition> function_definition
%type <StructureDefinition> struct_definition

%type <std::vector<VariableDefinition>> optional_variables_definition_list
%type <std::vector<VariableDefinition>> variables_definition_list
%type <VariableDefinition> variable_definition

%type <TypeDescription> var_type

%start root

%%

root
    : %empty
    | global_statements_list
    ;

global_statements_list
    : global_statement command_separator
    | global_statements_list global_statement command_separator
    ;

global_statement
    : version_marker
    | shader_definition { cb->addShaderDefinition($1); }
    | STRING_LITERAL { std::cerr << "found string: " << $1 << std::endl; }
    | GLSL_CODE_BLOCK { std::cerr << "found code: " << $1 << std::endl; }
    ;

shader_definition
    : SHADER shader_name '{' shader_properties_list '}'
    {
        $$ = $4;
        $$.name = $2;
    }
    ;

shader_name
    : IDENTIFIER { $$ = $1; }
    | STRING_LITERAL { $$ = $1; }
    ;

shader_properties_list
    : %empty
    {
        $$ = ShaderDefinition{};
    }
    | shader_properties_list shader_shared_code_property command_separator
    {
        $$ = $1;
        $$.sharedCode = $2;
    }
    | shader_properties_list function_definition command_separator
    {
        $$ = $1;
        enlist($$.functions, $2);
    }
    | shader_properties_list struct_definition command_separator
    {
        $$ = $1;
        enlist($$.structures, $2);
    }
    ;

shader_shared_code_property
    : SHARED GLSL_CODE_BLOCK { $$ = $2; }
    ;

function_definition
    : FUNC IDENTIFIER '(' optional_variables_definition_list ')' ':'
        variable_definition GLSL_CODE_BLOCK
    {
        $$ = FunctionDefinition{};
        $$.name = $2;
        $$.inputVariables = $4;
        $$.outputVariables = {$7};
        $$.code = $8;
    }
    | FUNC IDENTIFIER '(' optional_variables_definition_list ')' ':'
        '(' variables_definition_list ')' GLSL_CODE_BLOCK
    {
        $$ = FunctionDefinition{};
        $$.name = $2;
        $$.inputVariables = $4;
        $$.outputVariables = $8;
        $$.code = $10;
    }
    ;

struct_definition
    : STRUCT IDENTIFIER '{' variables_definition_list '}'
    {
        $$ = StructureDefinition{};
        $$.name = $2;
        $$.members = $4;
    }
    ;

optional_variables_definition_list
    : %empty { $$ = {}; }
    | variables_definition_list { $$ = $1; }
    ;

variables_definition_list
    : variable_definition { $$ = {$1}; }
    | variables_definition_list ',' variable_definition
    {
        $$ = $1;
        enlist($$, $3);
    }
    ;

variable_definition
    : var_type IDENTIFIER { $$ = VariableDefinition{$2, $1}; }
    ;

var_type
    : GLSL_TYPE { $$ = TypeDescription{$1, TypeCategory::Primitive}; }
    | IDENTIFIER { $$ = TypeDescription{$1, TypeCategory::UserDefined}; }
    ;

version_marker
    : VERSION INTEGER_CONSTANT { cb->setVersion($2); }
    | VERSION GLSL INTEGER_CONSTANT IDENTIFIER { cb->setGLSLVersion($3, $4); }
    ;

command_separator
    : ';'
    ;

%%

void sb::shabuiParser::error(
    const sb::shabuiParser::location_type& l,
    const std::string& m
)
{
    throw sb::shabuiParser::syntax_error(l, m);
}
