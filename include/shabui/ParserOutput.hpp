#pragma once
#include <string>
#include "ShabuiAst.hpp"

namespace sb
{

class ParserOutput
{
public:
    void setVersion(int major);
    void setGLSLVersion(int version, std::string profile);

    void addFunctionDefinition(const FunctionDefinition& functionDefinition);
    void addShaderDefinition(const ShaderDefinition& shaderDefinition);

    const ShabuiScope &getGlobalScope() { return _globalScope; }

private:
    ShabuiScope _globalScope;
};

}
