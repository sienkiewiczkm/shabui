#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "shabui/GLSLLoader.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "usage: " << argv[0] << " shaderfile";
        return EXIT_FAILURE;
    }

    sb::GLSLLoader loader;
    auto result = loader.loadFile(argv[1]);

    std::cerr << "Vertex Shader Output:" << std::endl;
    std::cerr << result.vertexShaderCode << std::endl;

    std::cerr << "Fragment Shader Output:" << std::endl;
    std::cerr << result.fragmentShaderCode << std::endl;

    return EXIT_SUCCESS;
}
