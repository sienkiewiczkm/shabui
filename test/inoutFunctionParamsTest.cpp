#include "sharedTest.hpp"

int main() {
    auto code = compile("inoutFunctionParamsTest.sbl");
    std::cerr << code.vertexShaderCode << std::endl << code.fragmentShaderCode;
    return EXIT_FAILURE;
}
