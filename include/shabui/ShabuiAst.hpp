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

struct VariableProperty
{
    VariableProperty();
    VariableProperty(const std::string& name, const std::string& value);

    std::string name;
    std::string value;
};

struct VariableDefinition
{
    VariableDefinition();
    VariableDefinition(
        const std::string& name,
        const TypeDescription& type,
        const std::string& option = {},
        const int arraySize = -1
    );

    std::string name;
    TypeDescription type;
    std::string option;
    int arraySize; // if -1 then it's not an array
    std::vector<VariableProperty> properties;
};

struct FunctionDefinition
{
    std::string name;
    std::vector<VariableDefinition> inputVariables;
    std::vector<VariableDefinition> outputVariables;
    std::vector<std::string> requirements;
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

    const StructureDefinition* getStructure(const std::string& name) const;
    const FunctionDefinition* getFunction(const std::string& name) const;
};

struct ShabuiScope
{
    int glslVersion;
    std::string glslProfileName;
    std::vector<FunctionDefinition> functions;
    std::vector<ShaderDefinition> shaders;
    std::vector<std::string> dependencies;

    const FunctionDefinition* getFunction(const std::string& name) const;
};

}
