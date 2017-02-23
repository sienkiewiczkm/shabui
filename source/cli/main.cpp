#include <cstdio>
#include <string>
#include <sstream>
#include "shabuiParser.hxx"
#include "shabuiScanner.hpp"
#include "shabuiAst.hpp"

int main(int argc, char **argv)
{
    std::string filecontents = "version";
    std::istringstream ss(filecontents);

    sb::shabuiScanner scanner(&ss);
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
