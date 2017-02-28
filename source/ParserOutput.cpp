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

void ParserOutput::addShaderDefinition(const ShaderDefinition& shaderDefinition)
{
    _globalScope.shaders.push_back(shaderDefinition);
}

}
