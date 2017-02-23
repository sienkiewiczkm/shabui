%skeleton "lalr1.cc"
%require "3.0"
%parse-param {sb::shabuiScanner* scanner} {ParserOutput* cb}
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
    #include "location.hh"

    namespace sb
    {
        class shabuiScanner;
    }

    struct ParserOutput
    {
        virtual void setVersion(std::string name) = 0;
    };
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

%token <std::string> STRING_LITERAL
%token <std::string> GLSL_CODE_BLOCK

%token VERSION SHADER FUNC SHARED
%token COLON
%token GLSL_TYPE

%token <int> INTEGER_CONSTANT
%start root

%%

root
    : VERSION { std::cerr << "keyword version found" << std::endl; }
    | STRING_LITERAL { std::cerr << "found string: " << $1 << std::endl; }
    | GLSL_CODE_BLOCK { std::cerr << "found code: " << $1 << std::endl; }
    ;

%%

void sb::shabuiParser::error(
    const sb::shabuiParser::location_type& l,
    const std::string& m
)
{
    throw sb::shabuiParser::syntax_error(l, m);
}
