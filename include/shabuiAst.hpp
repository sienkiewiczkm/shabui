#pragma once

#include <string>
#include <vector>

namespace sb
{

struct VariableDefinition
{
    VariableDefinition();
    VariableDefinition(const std::string& name, const std::string &type);

    std::string name;
    std::string type;
};

struct FunctionDefinition
{
    std::string name;
    std::vector<VariableDefinition> inputVariables;
    std::vector<VariableDefinition> outputVariables;
    std::string code;
};

struct StructureDefinition
{
    std::string name;
    std::vector<VariableDefinition> members;
};

struct ShaderDefinition
{
    std::string name;
    std::string sharedCode;
    std::vector<StructureDefinition> structures;
    std::vector<FunctionDefinition> functions;
};

struct ShabuiGlobalScope
{
    int glslVersion;
    std::string glslProfileName;
    std::vector<ShaderDefinition> shaders;
};

}
