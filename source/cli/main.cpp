#include <cstdio>
#include <string>
#include <sstream>
#include "shabuiParser.hxx"
#include "shabuiScanner.hpp"
#include "shabuiAst.hpp"
#include "stringUtils.hpp"
#include "shaderGenerators.hpp"

int main(int argc, char **argv)
{
    sb::ParserOutput output;
    sb::shabuiScanner scanner(&std::cin);
    sb::shabuiParser parser(&scanner, &output);

    sb::VertexShaderGenerator vertexGenerator;

    try
    {
        parser.parse();

        auto& globalScope = output.getGlobalScope();
        std::cout << "Generating: " << std::endl
            << vertexGenerator.generate(globalScope, globalScope.shaders[0]);
    }
    catch (sb::shabuiParser::syntax_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
