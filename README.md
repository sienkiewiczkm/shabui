# Shabui

Shabui is **sha**der **bui**lding tool designed to simplify my personal projects. It is special language that helps generation shaders in single GLSL shader pipeline. For current features see issues and code directly. This is **not** mature project yet.

## Syntax

### Example file
```
version 1;
version glsl 330 core;

shader "Example Shader"
{
    shared
    <<<
        uniform vec3 lightDirection;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
    >>>;

    struct vertexLayout
    {
        vec3 position {location = 0},
        vec3 normal   {location = 1}
    };

    struct vertexOutput
    {
        vec3 Normal,
        vec3 ViewLightDirection
    };

    func vertex(vertexLayout vertex): vertexOutput result
    <<<
        vec4 viewPosition = view * model * vec4(vertex.position, 1.0);
        gl_Position = projection * viewPosition;

        result.Normal = normalize(
            (view * (transpose(inverse(model)) * vec4(vertex.normal, 0))).xyz
        );

        result.ViewLightDirection = normalize(
            (view * vec4(lightDirection, 0)).xyz
        );
    >>>;

    func fragment(vertexOutput vsOut): vec4 result
    <<<
        vec3 lightDir = normalize(vsOut.ViewLightDirection);
        vec3 normal = normalize(vsOut.Normal);
        float diffuse = dot(lightDir, normal);
        result = vec4(vec3(diffuse), 1.0);
    >>>;
};
```

### Syntax cheatsheet
Shabui is case sensitive. Every statement should end with `;`.

| Code | Allowed in | Meaning |
|------|------------|---------|
|`version VERSION`|global|Marks version of a shabui file. Currently can be anything because exact version 1 grammar hasn't been estabilished yet.|
|`version glsl VERSION PROFILE`|global|Specifies exact version of GLSL used in this file. It will generate `#version VERSION PROFILE` on top of each GLSL shader file.|
|`shader "SHADER NAME" { ... }`|global|Marks shader section.|
|`struct name { ... }`|shader|Creates a structure which can be used as interface block. If interface block is not available (eg. input for vertex shader) contents of this structure will be put into global scope and `vertex.` (see example above) will be removed from GLSL code string.|
|`varType varName { location: INT }`|struct|Optional properties of variable definition. It marks layout for inputs for Vertex Shader. It generates `layout(location=INT) ` in front of code that generates that variable in GLSL.|
|`func name(...inputs...): ...outputs... <<<code>>>`|shader|Defines shader function. Inputs and outputs are C-style variable lists, if multiple outputs are present they have to be surrounded with parentheses. All inputs/outputs must be named. Currently, if non-primitive type is used in function it must be the only argument.|
|`<<< GLSL code block >>>`|argument|Code will be copied and pasted directly, except changes explained in struct section.

## Usage (CMake)
Add project as submodule, include that in `CMakeLists.txt` and then include `shabui/GLSLLoader.hpp` where you need it. Look at source of that file for details. 

