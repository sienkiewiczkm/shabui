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

struct ShaderDefinition
{
    std::string name;
    std::string sharedCode;
    std::vector<FunctionDefinition> functions;
};

}
