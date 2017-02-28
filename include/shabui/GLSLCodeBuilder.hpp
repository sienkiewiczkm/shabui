#pragma once
#include <string>
#include <sstream>
#include "ShabuiAst.hpp"
#include "GLSLShaderProgramCode.hpp"

namespace sb
{

struct GLSLShaderBuildCache
{
    GLSLShaderBuildCache();

    bool isInputInterfaceBlockAvailable;
    bool isOutputInterfaceBlockAvailable;

    std::stringstream preMainCode;
    std::stringstream postMainCode;

    std::string mainFunctionCode;
};

class GLSLCodeBuilder
{
public:
    GLSLCodeBuilder();
    ~GLSLCodeBuilder();

    GLSLShaderProgramCode build(
        const ShabuiScope& globalScope,
        const ShaderDefinition& shaderDef
    );

private:
    enum class FunctionVariableListType
    {
        Input,
        Output
    };

    std::string buildVertexShader();
    std::string buildTessControlShader();
    std::string buildTessEvalShader();
    std::string buildGeometryShader();
    std::string buildFragmentShader();

    std::string buildCurrentAsStandardShader();

    void buildCache();

    std::string buildHeader();
    std::string buildSharedCodeSection();
    std::string buildDependencies(const FunctionDefinition& funcDef);

    std::string buildMain();
    std::string buildFunction(const FunctionDefinition& funcDef);

    void buildInputsOutputs();

    std::string buildIOBlock(
        const std::vector<VariableDefinition>& varList,
        FunctionVariableListType varListType
    );

    std::string buildDecoratedVarList(
        const std::vector<VariableDefinition>& varList,
        const std::string& varDecorator
    );

    std::string buildMainFunctionCode();

    bool areAllPrimitiveVars(const std::vector<VariableDefinition>& varList);

    const ShabuiScope* _scope;
    const ShaderDefinition* _shaderDef;
    const FunctionDefinition* _mainFunction;

    GLSLShaderBuildCache _cache;
};

}
