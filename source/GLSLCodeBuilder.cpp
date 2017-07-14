#include <iostream>
#include <regex>
#include "shabui/GLSLCodeBuilder.hpp"

namespace sb
{

GLSLShaderBuildCache::GLSLShaderBuildCache()
{
}

GLSLCodeBuilder::GLSLCodeBuilder()
{
}

GLSLCodeBuilder::~GLSLCodeBuilder()
{
}

GLSLShaderProgramCode GLSLCodeBuilder::build(
    const ShabuiScope& globalScope,
    const ShaderDefinition& shaderDef
)
{
    _scope = &globalScope;
    _shaderDef = &shaderDef;

    GLSLShaderProgramCode code;
    code.vertexShaderCode = buildVertexShader();
    code.fragmentShaderCode = buildFragmentShader();
    return code;
}

std::string GLSLCodeBuilder::buildVertexShader()
{
    _mainFunction = _shaderDef->getFunction("vertex");

    if (_mainFunction == nullptr)
    {
        return {};
    }

    buildCache();
    _cache.isInputInterfaceBlockAvailable = false;
    _cache.isOutputInterfaceBlockAvailable = true;

    return buildCurrentAsStandardShader();
}

std::string GLSLCodeBuilder::buildTessControlShader()
{
    return {};
}

std::string GLSLCodeBuilder::buildTessEvalShader()
{
    return {};
}

std::string GLSLCodeBuilder::buildGeometryShader()
{
    return {};
}

std::string GLSLCodeBuilder::buildFragmentShader()
{
    _mainFunction = _shaderDef->getFunction("fragment");

    if (_mainFunction == nullptr)
    {
        return {};
    }

    buildCache();
    _cache.isInputInterfaceBlockAvailable = true;
    _cache.isOutputInterfaceBlockAvailable = false;

    return buildCurrentAsStandardShader();
}

std::string GLSLCodeBuilder::buildCurrentAsStandardShader()
{
    std::ostringstream ss;

    ss << buildHeader() << std::endl;
    ss << buildSharedCodeSection() << std::endl;
    ss << buildMain() << std::endl;

    return ss.str();
}

void GLSLCodeBuilder::buildCache()
{
    _cache = GLSLShaderBuildCache{};
    _cache.mainFunctionCode = _mainFunction->code;
}

std::string GLSLCodeBuilder::buildHeader()
{
    std::ostringstream ss;
    ss << "#version " << _scope->glslVersion << " " << _scope->glslProfileName
        << std::endl;
    return ss.str();
}

std::string GLSLCodeBuilder::buildSharedCodeSection()
{
    return _shaderDef->sharedCode;
}

std::string GLSLCodeBuilder::buildDependencies(
    const FunctionDefinition& funcDef
)
{
    std::ostringstream ss;
    for (const auto& dependency: funcDef.requirements)
    {
        auto dependencyFunc = _scope->getFunction(dependency);
        if (dependencyFunc == nullptr)
        {
            throw std::logic_error(
                "Dependency function \"" + dependency + "\" not found."
            );
        }

        ss << buildFunction(*dependencyFunc) << std::endl;
    }

    return ss.str();
}

std::string GLSLCodeBuilder::buildMain()
{
    buildInputsOutputs();

    std::ostringstream ss;
    ss << buildDependencies(*_mainFunction);
    ss << _cache.preMainCode.str() << std::endl;
    ss << buildMainFunctionCode();
    ss << _cache.postMainCode.str() << std::endl;
    return ss.str();
}

std::string GLSLCodeBuilder::buildFunction(const FunctionDefinition& funcDef)
{
    if (funcDef.outputVariables.size() != 1)
    {
        throw std::logic_error(
            "Function \"" + funcDef.name
            + "\" used as standard function should return exactly one value."
        );
    }

    std::ostringstream ss;
    ss << buildDependencies(funcDef);
    ss << funcDef.outputVariables[0].type.name << " " << funcDef.name;
    ss << "(";

    const auto numInputs = funcDef.inputVariables.size();
    for (auto i = 0; i < numInputs; ++i)
    {
        const auto& variable = funcDef.inputVariables[i];
        ss << variable.option << " " << variable.type.name << " "
            << variable.name;

        if (variable.arraySize > 0)
        {
            ss << "[" << variable.arraySize << "]";
        }

        if (i + 1 < numInputs)
        {
            ss << ", ";
        }
    }

    ss << ") {" << funcDef.outputVariables[0].type.name << " "
        << funcDef.outputVariables[0].name << ";" << std::endl
        << funcDef.code
        << "return " << funcDef.outputVariables[0].name << ";}" << std::endl;

    return ss.str();
}

void GLSLCodeBuilder::buildInputsOutputs()
{
    _cache.preMainCode << buildIOBlock(
        _mainFunction->inputVariables,
        FunctionVariableListType::Input
    );

    _cache.preMainCode << buildIOBlock(
        _mainFunction->outputVariables,
        FunctionVariableListType::Output
    );
}

std::string GLSLCodeBuilder::buildIOBlock(
    const std::vector<VariableDefinition>& varList,
    FunctionVariableListType varListType
)
{
    if (varList.size() == 0)
    {
        return {};
    }

    bool isInterfaceBlockAvailable =
        varListType == FunctionVariableListType::Input
        ? _cache.isInputInterfaceBlockAvailable
        : _cache.isOutputInterfaceBlockAvailable;

    std::string ioDecorator =
        varListType == FunctionVariableListType::Input
        ? "in"
        : "out";

    bool onlyPrimitives = areAllPrimitiveVars(varList);

    if (!onlyPrimitives)
    {
        if (varList.size() > 1)
        {
            throw std::logic_error(
                "If non-primitive is used it must be single argument."
            );
        }

        auto structureDef = _shaderDef->getStructure(varList[0].type.name);
        if (structureDef == nullptr)
        {
            throw std::logic_error(
                "Used structure is undefined."
            );
        }

        if (isInterfaceBlockAvailable)
        {
            std::ostringstream ss;
            ss << ioDecorator << " " << structureDef->name << "{" << std::endl;
            ss << buildDecoratedVarList(structureDef->members, {});
            ss << "} " << varList[0].name << ";" << std::endl;
            return ss.str();
        }
        else
        {
            // todo: check for name collisions
            std::regex e(varList[0].name + "\\.");
            _cache.mainFunctionCode =
                std::regex_replace(_cache.mainFunctionCode, e, "");
            return buildDecoratedVarList(structureDef->members, ioDecorator);
        }
    }

    return buildDecoratedVarList(varList, ioDecorator);
}

std::string GLSLCodeBuilder::buildDecoratedVarList(
    const std::vector<VariableDefinition>& varList,
    const std::string& varDecorator
)
{
    std::ostringstream ss;

    for (const auto& varDef: varList)
    {
        if (varDef.properties.size() > 0)
        {
            ss << "layout(location=" << varDef.properties[0].value << ") ";
        }

        ss << varDecorator << " " << varDef.option;
        ss << varDef.type.name << " " << varDef.name;

        if (varDef.arraySize > 0)
        {
            ss << "[" << varDef.arraySize << "]";
        }

        ss << ";" << std::endl;
    }

    return ss.str();
}

std::string GLSLCodeBuilder::buildMainFunctionCode()
{
    std::ostringstream ss;
    ss << "void main(void){" << _cache.mainFunctionCode << "}" << std::endl;
    return ss.str();
}

bool GLSLCodeBuilder::areAllPrimitiveVars(
    const std::vector<VariableDefinition>& varList
)
{
    return std::end(varList) == std::find_if(
        std::begin(varList),
        std::end(varList),
        [](const VariableDefinition& varDef)
        {
            return varDef.type.category != TypeCategory::Primitive;
        }
    );
}

}
