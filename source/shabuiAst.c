#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shabuiAst.h"

void shabuiListAppend(struct shabuiAst** list, struct shabuiAst* toAdd)
{
    if (*list == 0)
    {
        *list = toAdd;
        return;
    }

    struct shabuiAst* helper = *list;
    while (helper->next)
    {
        helper = helper->next;
    }

    helper->next = toAdd;
}

struct shabuiAst* shabuiMakeEmptyNode(enum shabuiNodeType nodeType)
{
    struct shabuiAst* node = malloc(sizeof(struct shabuiAst));
    if (!node)
    {
        shabuierror("malloc call failed. Out of memory.");
        return 0;
    }

    memset(node, 0, sizeof(struct shabuiAst));
    node->nodeType = nodeType;

    return node;
}

struct shabuiAst* shabuiMakeNumber(int value)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_NUMBER);
    node->value = value;
    return node;
}

struct shabuiAst* shabuiMakeString(const char* str)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_STRING_LITERAL);
    node->str = strdup(str);
    return node;
}

struct shabuiAst* shabuiMakeVersion(int major)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_VERSION);
    node->value = major;
    return node;
}

struct shabuiAst* shabuiMakeShader(
    struct shabuiAst* name,
    struct shabuiAst* propertyList
)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_SHADER);
    node->lhs = name;
    node->rhs = propertyList;
    return node;
}

struct shabuiAst* shabuiMakeVertexShader()
{
    return shabuiMakeEmptyNode(SB_NODE_PROGRAM_VERTEX);
}

struct shabuiAst* shabuiMakeFragmentShader()
{
    return shabuiMakeEmptyNode(SB_NODE_PROGRAM_FRAGMENT);
}

struct shabuiAst* shabuiMakeVariableDeclaration(
    struct shabuiAst* name,
    struct shabuiAst* type
)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_VARIABLE_DECLARATION);
    node->lhs = name;
    node->rhs = type;
    return node;
}

struct shabuiAst* shabuiMakeSharedCodeBlock(struct shabuiAst* code)
{
    struct shabuiAst* node = shabuiMakeEmptyNode(SB_NODE_SHARED_CODE);
    node->lhs = code;
    return node;
}

