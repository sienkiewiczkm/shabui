#include <cstdio>
#include <string>
#include <sstream>
#include "shabuiParser.hxx"
#include "shabuiScanner.hpp"
#include "shabuiAst.hpp"
#include "stringUtils.hpp"

int main(int argc, char **argv)
{
    sb::shabuiScanner scanner(&std::cin);
    sb::shabuiParser parser(&scanner, nullptr);

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
