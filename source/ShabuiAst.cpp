#include "shabui/ShabuiAst.hpp"

namespace sb
{

TypeDescription::TypeDescription():
    name{},
    category{TypeCategory::Unknown}
{
}

TypeDescription::TypeDescription(
    const std::string& name,
    TypeCategory category
):
    name{name},
    category{category}
{
}

VariableDefinition::VariableDefinition():
    name{},
    type{}
{
}

VariableDefinition::VariableDefinition(
    const std::string& name,
    const TypeDescription& type
):
    name{name},
    type{type}
{
}

VariableProperty::VariableProperty():
    name{},
    value{}
{
}

VariableProperty::VariableProperty(
    const std::string& name,
    const std::string& value
):
    name{name},
    value{value}
{
}

const StructureDefinition* ShaderDefinition::getStructure(
    const std::string& name
) const
{
    auto item = std::find_if(
        std::begin(structures),
        std::end(structures),
        [&name](const StructureDefinition& structDef)
        {
            return name == structDef.name;
        }
    );

    if (item == std::end(structures))
    {
        return nullptr;
    }

    return &(*item);
}

const FunctionDefinition* ShaderDefinition::getFunction(
    const std::string& name
) const
{
    auto item = std::find_if(
        std::begin(functions),
        std::end(functions),
        [&name](const FunctionDefinition& funcDef)
        {
            return name == funcDef.name;
        }
    );

    if (item == std::end(functions))
    {
        return nullptr;
    }

    return &(*item);
}

const FunctionDefinition* ShabuiScope::getFunction(
    const std::string& name
) const
{
    auto item = std::find_if(
        std::begin(functions),
        std::end(functions),
        [&name](const FunctionDefinition& funcDef)
        {
            return name == funcDef.name;
        }
    );

    if (item == std::end(functions))
    {
        return nullptr;
    }

    return &(*item);
}

}
