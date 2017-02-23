#include <sstream>
#include <stdexcept>
#include "shaderGeneratorBase.hpp"

namespace sb
{

ShaderGeneratorBase::ShaderGeneratorBase()
{
}

std::string ShaderGeneratorBase::buildHeader(
    const ShabuiGlobalScope& globalScope
)
{
    std::stringstream ss;
    ss << "#version " << globalScope.glslVersion << " "
        << globalScope.glslProfileName << std::endl;
    return ss.str();
}

std::string ShaderGeneratorBase::buildMainFunction(
    const FunctionDefinition& functionDefinition
)
{
    std::stringstream ss;

    int locationCounter = 0;
    for (const auto& inputVar: functionDefinition.inputVariables)
    {
        ss << "layout (location = " << locationCounter << ") in ";
        ss << inputVar.type << " " << inputVar.name << ";" << std::endl;
        ++locationCounter;
    }

    for (const auto& outputVar: functionDefinition.outputVariables)
    {
        ss << "out " << outputVar.type << " " << outputVar.name << ";";
        ss << std::endl;
    }

    ss << "void main(void) {" << std::endl << functionDefinition.code;
    ss << "}" << std::endl;

    return ss.str();
}

std::string ShaderGeneratorBase::buildFunctionCode(
    const FunctionDefinition& functionDefinition
)
{
    std::stringstream ss;

    if (functionDefinition.outputVariables.size() > 1)
    {
        throw std::logic_error("GLSL functions can return only one value.");
    }

    std::stringstream glslCodeInitialization{};
    std::stringstream glslCodeCleanup{};

    if (functionDefinition.outputVariables.size() > 0)
    {
        auto outputVar = functionDefinition.outputVariables[0];
        glslCodeInitialization << outputVar.type << " "
            << outputVar.name << ";" << std::endl;
        glslCodeCleanup << "return " << outputVar.name << ";" << std::endl;
        ss << outputVar.type << " ";
    }
    else
    {
        ss << "void ";
    }

    ss << functionDefinition.name << "(";
    for (auto i = 0; i < functionDefinition.inputVariables.size(); ++i)
    {
        const auto& variable = functionDefinition.inputVariables[i];
        ss << variable.type << " " << variable.name;
        if ((i+1) < functionDefinition.inputVariables.size())
        {
            ss << ", ";
        }
    }

    ss << ") {" << std::endl;
    ss << glslCodeInitialization.str() << functionDefinition.code
        << glslCodeCleanup.str();
    ss << "}" << std::endl;

    return ss.str();
}

int ShaderGeneratorBase::findShaderFunctionIndex(
    const ShaderDefinition& shaderDef,
    std::string wantedName
)
{
    for (auto i = 0; i < shaderDef.functions.size(); ++i)
    {
        if (shaderDef.functions[i].name == wantedName)
        {
            return i;
        }
    }

    return -1;
}


}
