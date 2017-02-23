#include <iostream>
#include "parserOutput.hpp"

namespace sb
{

void ParserOutput::setVersion(int major)
{
    std::cout << "version registered: " << major << std::endl;
}

void ParserOutput::setGLSLVersion(int major, std::string profile)
{
    std::cout << "glsl version registered: " << major << " profile: " << profile
        << std::endl;
}

void ParserOutput::addShaderDefinition(const ShaderDefinition& shaderDefinition)
{
    std::cout << "shader registered: " << shaderDefinition.name << std::endl;
    std::cout << "\tshared code:" << shaderDefinition.sharedCode << std::endl;

    for (const auto& functionDef: shaderDefinition.functions)
    {
        std::cout << "\tfunction: " << functionDef.name << std::endl;

        std::cout << "\t\tinputs: " << std::endl;
        for (const auto& var: functionDef.inputVariables)
        {
            std::cout << "\t\t\ttype=" << var.type
                << " name=" << var.name << std::endl;
        }

        std::cout << "\t\toutputs: " << std::endl;
        for (const auto& var: functionDef.outputVariables)
        {
            std::cout << "\t\t\ttype=" << var.type
                << " name=" << var.name << std::endl;
        }

        std::cout << "\tcode: " << functionDef.code << std::endl;
    }
}

}