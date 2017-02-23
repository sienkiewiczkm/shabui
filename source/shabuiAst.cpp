#include "shabuiAst.hpp"

namespace sb
{

VariableDefinition::VariableDefinition():
    name{},
    type{}
{
}

VariableDefinition::VariableDefinition(
    const std::string& name,
    const std::string &type
):
    name{name},
    type{type}
{
}

}
