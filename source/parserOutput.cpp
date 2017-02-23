#include <iostream>
#include "parserOutput.hpp"

namespace sb
{

void ParserOutput::setVersion(int major)
{
    std::cout << "version registered: " << major << std::endl;
}

void ParserOutput::setGLSLVersion(int major, std::string profile)
{
    std::cout << "glsl version registered: " << major << " profile: " << profile
        << std::endl;
}

}
