#include <iostream>
#include "shabui/ParserOutput.hpp"

namespace sb
{

void ParserOutput::setVersion(int major)
{
}

void ParserOutput::setGLSLVersion(int major, std::string profile)
{
    _globalScope.glslVersion = major;
    _globalScope.glslProfileName = profile;
}

void ParserOutput::addFunctionDefinition(
    const FunctionDefinition& functionDefinition
)
{
    if (functionDefinition.outputVariables.size() > 1)
    {
        throw std::logic_error(
            "Global functions can return only one value."
        );
    }

    _globalScope.functions.push_back(functionDefinition);
}

void ParserOutput::addShaderDefinition(const ShaderDefinition& shaderDefinition)
{
    _globalScope.shaders.push_back(shaderDefinition);
}

}
