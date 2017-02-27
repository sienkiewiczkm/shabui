#include <cstdio>
#include <string>
#include <sstream>
#include "ShabuiParser.hxx"
#include "ShabuiScanner.hpp"
#include "ShabuiAst.hpp"
#include "StringUtils.hpp"
#include "GLSLCodeBuilder.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<sb::ParserOutput> output =
        std::make_shared<sb::ParserOutput>();

    sb::shabuiScanner scanner(&std::cin);
    sb::shabuiParser parser(&scanner, output.get());

    try
    {
        parser.parse();

        sb::GLSLCodeBuilder builder;
        auto result = builder.build(
            output->getGlobalScope(),
            output->getGlobalScope().shaders[0]
        );

        std::cerr << "Vertex Shader Output:" << std::endl;
        std::cerr << result.vertexShaderCode << std::endl;

        std::cerr << std::endl << "Fragment Shader Output:" << std::endl;
        std::cerr << result.fragmentShaderCode << std::endl;
    }
    catch (sb::shabuiParser::syntax_error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
