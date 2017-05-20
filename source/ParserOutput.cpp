#include <iostream>
#include "shabui/ParserOutput.hpp"

namespace sb
{

ParserOutput::ParserOutput():
    _isVersionSet{false},
    _isGLSLVersionSet{false},
    _dependencyLoadMode{false}
{
}

void ParserOutput::addDependency(const std::string& file)
{
    _globalScope.dependencies.push_back(file);
}

void ParserOutput::setVersion(int major)
{
    _isVersionSet = true;
}

void ParserOutput::setGLSLVersion(int major, std::string profile)
{
    if (!_isGLSLVersionSet)
    {
        _globalScope.glslVersion = major;
        _globalScope.glslProfileName = profile;
        _isGLSLVersionSet = true;
    }
    else
    {
        if (_globalScope.glslVersion != major
            || _globalScope.glslProfileName != profile)
        {
            std::cerr << "warning: include version doesn't match target";
        }
    }
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

void ParserOutput::startDependencyBuilding()
{
    _dependencyLoadMode = true;
}

}
