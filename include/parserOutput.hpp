#pragma once
#include <string>
#include "shabuiAst.hpp"

namespace sb
{

class ParserOutput
{
public:
    void setVersion(int major);
    void setGLSLVersion(int version, std::string profile);
    void addShaderDefinition(const ShaderDefinition& shaderDefinition);
};

}
