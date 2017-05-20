#pragma once
#include <memory>
#include "GLSLShaderProgramCode.hpp"
#include "ParserOutput.hpp"

namespace sb
{

class GLSLLoaderDependencyResolver
{
public:
    virtual ~GLSLLoaderDependencyResolver() {}
    virtual std::unique_ptr<std::istream> getDependency(
        std::string dependencyName
    ) = 0;
};

class GLSLLoaderFileDependencyResolver:
    public GLSLLoaderDependencyResolver
{
public:
    GLSLLoaderFileDependencyResolver(std::string basePath);
    virtual ~GLSLLoaderFileDependencyResolver() {}
    virtual std::unique_ptr<std::istream> getDependency(
        std::string dependencyName
    );

private:
    std::string _basePath;
};

class GLSLLoader
{
public:
    GLSLLoader(GLSLLoaderDependencyResolver& dependencyResolver);
    GLSLShaderProgramCode loadFile(const std::string& filename);
    GLSLShaderProgramCode load(std::istream& input);

protected:
    void loadStream(std::istream& input);

private:
    std::shared_ptr<sb::ParserOutput> _output;
    GLSLLoaderDependencyResolver& _dependencyResolver;
};

}
