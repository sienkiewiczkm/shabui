#include "shabuiAst.hpp"

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

}
