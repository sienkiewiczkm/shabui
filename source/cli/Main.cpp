#include <cstdio>
#include <string>
#include <sstream>
#include "ShabuiParser.hxx"
#include "ShabuiScanner.hpp"
#include "ShabuiAst.hpp"
#include "StringUtils.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<sb::ParserOutput> output =
        std::make_shared<sb::ParserOutput>();

    sb::shabuiScanner scanner(&std::cin);
    sb::shabuiParser parser(&scanner, output.get());

    try
    {
        parser.parse();
    }
    catch (sb::shabuiParser::syntax_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
