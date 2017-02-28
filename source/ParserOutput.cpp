#include <iostream>
#include "shabui/ParserOutput.hpp"

namespace sb
{

void ParserOutput::setVersion(int major)
{
    std::cout << "version registered: " << major << std::endl;
}

void ParserOutput::setGLSLVersion(int major, std::string profile)
{
    _globalScope.glslVersion = major;
    _globalScope.glslProfileName = profile;

    std::cout << "glsl version registered: " << major << " profile: " << profile
        << std::endl;
}

void ParserOutput::addShaderDefinition(const ShaderDefinition& shaderDefinition)
{
    _globalScope.shaders.push_back(shaderDefinition);

    std::cout << "shader registered: " << shaderDefinition.name << std::endl;
    std::cout << "\tshared code:" << shaderDefinition.sharedCode << std::endl;

    for (const auto& functionDef: shaderDefinition.functions)
    {
        std::cout << "\tfunction: " << functionDef.name << std::endl;

        std::cout << "\t\tinputs: " << std::endl;
        for (const auto& var: functionDef.inputVariables)
        {
            std::cout << "\t\t\ttype=" << var.type.name
                << " name=" << var.name << std::endl;
        }

        std::cout << "\t\toutputs: " << std::endl;
        for (const auto& var: functionDef.outputVariables)
        {
            std::cout << "\t\t\ttype=" << var.type.name
                << " name=" << var.name << std::endl;
        }

        std::cout << "\tcode: " << functionDef.code << std::endl;
    }

    for (const auto& structDef: shaderDefinition.structures)
    {
        std::cout << "\tstructure: " << structDef.name << std::endl;
        std::cout << "\t\tmembers: " << std::endl;
        for (const auto& var: structDef.members)
        {
            std::cout << "\t\t\ttype=" << var.type.name
                << " name=" << var.name << std::endl;
        }
    }
}

}
