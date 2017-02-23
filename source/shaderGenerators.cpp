#include "shaderGenerators.hpp"
#include <sstream>

namespace sb
{

VertexShaderGenerator::VertexShaderGenerator()
{
}

std::string VertexShaderGenerator::generate(
    const ShabuiGlobalScope& globalScope,
    const ShaderDefinition& shaderDefinition
)
{
    std::stringstream ss;

    auto vertexShaderIndex = findShaderFunctionIndex(
        shaderDefinition,
        "vertex"
    );

    ss << buildHeader(globalScope)
        << shaderDefinition.sharedCode
        << buildMainFunction(shaderDefinition.functions[vertexShaderIndex]);
    return ss.str();
}

}
