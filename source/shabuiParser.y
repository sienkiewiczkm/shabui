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

%token VERSION SHADER FUNC SHARED GLSL
%token COLON
%token GLSL_TYPE

%token <int> INTEGER_CONSTANT

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
    | STRING_LITERAL { std::cerr << "found string: " << $1 << std::endl; }
    | GLSL_CODE_BLOCK { std::cerr << "found code: " << $1 << std::endl; }
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
