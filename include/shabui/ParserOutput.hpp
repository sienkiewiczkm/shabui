#pragma once
#include <set>
#include <string>
#include "ShabuiAst.hpp"

namespace sb
{

class ParserOutput
{
public:
    ParserOutput();

    void addDependency(const std::string& file);

    void setVersion(int major);
    void setGLSLVersion(int version, std::string profile);

    void addFunctionDefinition(const FunctionDefinition& functionDefinition);
    void addShaderDefinition(const ShaderDefinition& shaderDefinition);

    const ShabuiScope &getGlobalScope() { return _globalScope; }

    void startDependencyBuilding();

private:
    bool _isVersionSet;
    bool _isGLSLVersionSet;
    bool _dependencyLoadMode;

    ShabuiScope _globalScope;
};

}
