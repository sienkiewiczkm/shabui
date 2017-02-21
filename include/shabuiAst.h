#ifndef __SHABUI_AST_H__
#define __SHABUI_AST_H__

enum shabuiNodeType
{
    SB_NODE_UNKNOWN = 0,
    SB_NODE_STRING_LITERAL,
    SB_NODE_NUMBER,
    SB_NODE_VERSION,
    SB_NODE_SHADER
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

struct shabuiAst* shabuiListAppend(
    struct shabuiAst* list,
    struct shabuiAst* toAdd
);

struct shabuiAst* shabuiMakeEmptyNode(enum shabuiNodeType nodeType);
struct shabuiAst* shabuiMakeNumber(int value);
struct shabuiAst* shabuiMakeString(const char* str);
struct shabuiAst* shabuiMakeVersion(struct shabuiAst* versionNumber);

#endif //__SHABUI_AST_H__
