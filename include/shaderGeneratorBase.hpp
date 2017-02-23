#pragma once
#include <string>
#include "shabuiAst.hpp"

namespace sb
{

class ShaderGeneratorBase
{
public:
    ShaderGeneratorBase();
    virtual ~ShaderGeneratorBase() = default;

    virtual std::string generate(
        const ShabuiGlobalScope& globalScope,
        const ShaderDefinition& shaderDefinition
    ) = 0;

protected:
    std::string buildHeader(const ShabuiGlobalScope& globalScope);
    std::string buildMainFunction(const FunctionDefinition& functionDefinition);
    std::string buildFunctionCode(const FunctionDefinition& functionDefinition);

    int findShaderFunctionIndex(
        const ShaderDefinition& shaderDef,
        std::string wantedName
    );
};

};
