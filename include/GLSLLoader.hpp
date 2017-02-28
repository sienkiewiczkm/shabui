#pragma once
#include "GLSLShaderProgramCode.hpp"

namespace sb
{

class GLSLLoader
{
public:
    GLSLShaderProgramCode loadFile(const std::string& filename) const;
    GLSLShaderProgramCode load(std::istream& input) const;
};

}
