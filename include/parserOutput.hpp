#pragma once
#include <string>

namespace sb
{

class ParserOutput
{
public:
    void setVersion(int major);
    void setGLSLVersion(int version, std::string profile);
};

}
