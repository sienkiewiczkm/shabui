#include <fstream>
#include <memory>
#include <stdexcept>
#include "GLSLLoader.hpp"
#include "GLSLCodeBuilder.hpp"
#include "ShabuiParser.hxx"
#include "ShabuiScanner.hpp"

namespace sb
{

GLSLShaderProgramCode GLSLLoader::loadFile(const std::string& filename) const
{
    std::ifstream shaderFile{filename};
    if (!shaderFile.is_open())
    {
        throw std::invalid_argument{
            "Requested file \"" + filename + "\" cannot be opened."
        };
    }

    return load(shaderFile);
}

GLSLShaderProgramCode GLSLLoader::load(std::istream& input) const
{
    auto output = std::make_shared<sb::ParserOutput>();
    sb::shabuiScanner scanner{&input};
    sb::shabuiParser parser{&scanner, output.get()};

    try
    {
        parser.parse();
    }
    catch (sb::shabuiParser::syntax_error& e)
    {
        // todo: extract exception from parser and remove this printout
        std::cerr << e.what() << std::endl;
        throw;
    }

    if (output->getGlobalScope().shaders.size() != 1)
    {
        throw std::logic_error{
            "File must contain exactly one shader definition in current version"
        };
    }

    sb::GLSLCodeBuilder codeBuilder;
    auto code = codeBuilder.build(
        output->getGlobalScope(),
        output->getGlobalScope().shaders[0]
    );

    return code;
}

}
