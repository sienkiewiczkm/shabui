#pragma once
#include "shaderGeneratorBase.hpp"

namespace sb
{

class VertexShaderGenerator : ShaderGeneratorBase
{
public:
    VertexShaderGenerator();
    virtual ~VertexShaderGenerator() = default;

    virtual std::string generate(
        const ShabuiGlobalScope& globalScope,
        const ShaderDefinition& shaderDefinition
    );
};

}
