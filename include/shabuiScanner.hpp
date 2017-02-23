#pragma once

#undef yyFlexLexer
#include <FlexLexer.h>
#include "shabuiParser.hxx"

#undef YY_DECL
#define YY_DECL int sb::shabuiScanner::lex( \
                    sb::shabuiParser::semantic_type* yylval, \
                    sb::shabuiParser::location_type* yylloc)

namespace sb
{
    class shabuiScanner : public yyFlexLexer
    {
    public:
        explicit shabuiScanner(
            std::istream* input = nullptr,
            std::ostream* output = nullptr
        );

        int lex(
            shabuiParser::semantic_type* yylval,
            shabuiParser::location_type* yylloc
        );
    };
}
