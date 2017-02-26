#pragma once

#include <string>
#include <vector>

namespace sb
{

enum class TypeCategory
{
    Unknown,
    Primitive,
    UserDefined
};

struct TypeDescription
{
    TypeDescription();
    TypeDescription(const std::string& name, TypeCategory category);

    std::string name;
    TypeCategory category;
};

struct VariableDefinition
{
    VariableDefinition();
    VariableDefinition(const std::string& name, const TypeDescription& type);

    std::string name;
    TypeDescription type;
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
