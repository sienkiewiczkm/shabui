#include <cstdlib>
#include <iostream>
#include "shabui/GLSLLoader.hpp"

sb::GLSLShaderProgramCode compile(const std::string& filename) {
    try {
        sb::GLSLLoader loader;
        auto code = loader.loadFile(filename);
        return code;
    } catch (std::invalid_argument &arg) {
        std::cerr << "Exception: " << arg.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
