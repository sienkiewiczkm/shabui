#ifndef __SHABUI_AST_H__
#define __SHABUI_AST_H__

enum shabuiNodeType
{
    SB_NODE_UNKNOWN = 0,
    SB_NODE_NUMBER,
    SB_NODE_IDENTIFIER,
    SB_NODE_STRING_LITERAL,
    SB_NODE_GLSL_CODE,
    SB_NODE_VERSION,
    SB_NODE_VARIABLE_DECLARATION,
    SB_NODE_SHADER,
    SB_NODE_PROGRAM_VERTEX,
    SB_NODE_PROGRAM_TESS_CONTROL,
    SB_NODE_PROGRAM_TESS_EVAL,
    SB_NODE_PROGRAM_GEOMETRY,
    SB_NODE_PROGRAM_FRAGMENT,
    SB_NODE_FUNCTION_INPUTS,
    SB_NODE_FUNCTION_OUTPUTS,
    SB_NODE_FUNCTION_CODE,
    SB_NODE_SHARED_CODE
};

struct shabuiAst
{
    enum shabuiNodeType nodeType;
    struct shabuiAst* next;
    struct shabuiAst* lhs;
    struct shabuiAst* rhs;
    union {
        int value;
        char* str;
    };
};

// todo: unwanted global
struct shabuiAst *lastShabuiAst;

void shabuiListAppend(struct shabuiAst** list, struct shabuiAst* toAdd);

struct shabuiAst* shabuiMakeEmptyNode(enum shabuiNodeType nodeType);
struct shabuiAst* shabuiMakeNumber(int value);
struct shabuiAst* shabuiMakeString(const char* str);
struct shabuiAst* shabuiMakeVersion(int major);
struct shabuiAst* shabuiMakePropertyList();

struct shabuiAst* shabuiMakeShader(
    struct shabuiAst* name,
    struct shabuiAst* propertyList
);

struct shabuiAst* shabuiMakeVertexShader();
struct shabuiAst* shabuiMakeFragmentShader();

struct shabuiAst* shabuiMakeVariableDeclaration(
    struct shabuiAst* name,
    struct shabuiAst* type
);

struct shabuiAst* shabuiMakeSharedCodeBlock(struct shabuiAst* code);

#endif //__SHABUI_AST_H__
