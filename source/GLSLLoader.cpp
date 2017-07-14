#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include "shabui/GLSLLoader.hpp"
#include "shabui/GLSLCodeBuilder.hpp"
#include "shabui/ShabuiParser.hxx"
#include "shabui/ShabuiScanner.hpp"

namespace sb
{

GLSLLoaderFileDependencyResolver::GLSLLoaderFileDependencyResolver(
    std::string basePath
):
    _basePath{basePath}
{
}

std::unique_ptr<std::istream> GLSLLoaderFileDependencyResolver::getDependency(
    std::string dependencyName
)
{
    // todo: fix it
    auto olddep = dependencyName;
    auto lastSeperatorIdx = _basePath.find_last_of("/\\");
    if (lastSeperatorIdx != std::string::npos)
    {
        dependencyName =
            _basePath.substr(0, lastSeperatorIdx+1) + dependencyName;
    }

    auto fileHandlePtr = std::unique_ptr<std::ifstream>(
        new std::ifstream(dependencyName)
    );

    if (!fileHandlePtr->is_open())
        return nullptr;

    return std::unique_ptr<std::istream>(std::move(fileHandlePtr));
}

GLSLLoader::GLSLLoader(GLSLLoaderDependencyResolver& dependencyResolver):
    _dependencyResolver{dependencyResolver}
{
}


GLSLShaderProgramCode GLSLLoader::loadFile(
    const std::string& filename
)
{
    std::ifstream filestream{filename};

    if (!filestream.is_open())
    {
        throw std::invalid_argument{
            "Requested file \"" + filename + "\" cannot be opened."
        };
    }

    return load(filestream);
}

GLSLShaderProgramCode GLSLLoader::load(std::istream& input)
{
    _output = std::make_shared<sb::ParserOutput>();

    loadStream(input);

    auto& scope = _output->getGlobalScope();

    if (_output->getGlobalScope().shaders.size() != 1)
    {
        throw std::logic_error{
            "File must contain exactly one shader definition in current version"
        };
    }

    _output->startDependencyBuilding();

    std::set<std::string> loadedFiles;
    for (auto it = std::begin(scope.dependencies);
        it != std::end(scope.dependencies);
        ++it)
    {
        auto dep = *it;

        if (loadedFiles.find(dep) != std::end(loadedFiles))
            continue;

        loadedFiles.insert(dep);

        auto dependencyStream = _dependencyResolver.getDependency(dep);
        if (dependencyStream == nullptr)
        {
            throw std::logic_error{
                "Couldn't find dependency: " + dep
            };
        }

        loadStream(*dependencyStream);
    }

    sb::GLSLCodeBuilder codeBuilder;
    auto code = codeBuilder.build(
        _output->getGlobalScope(),
        _output->getGlobalScope().shaders[0]
    );

    return code;
}

void GLSLLoader::loadStream(std::istream& input)
{
    sb::shabuiScanner scanner{&input};
    sb::shabuiParser parser{&scanner, _output.get()};

    try
    {
        parser.parse();
    }
    catch (sb::shabuiParser::syntax_error& e)
    {
        // todo: extract exception from parser and remove this printout
        std::cerr << "line " << e.location.begin.line << "-"
            << e.location.end.line << " error: " << e.what() << std::endl;
        throw;
    }
}

}
