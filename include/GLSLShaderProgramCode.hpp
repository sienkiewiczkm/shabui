#pragma once
#include <string>

namespace sb
{

struct GLSLShaderProgramCode
{
    std::string vertexShaderCode;
    std::string tessControlShaderCode;
    std::string tessEvalShaderCode;
    std::string geometryShaderCode;
    std::string fragmentShaderCode;
};

}
