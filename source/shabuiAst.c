#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shabuiAst.h"

struct shabuiAst* shabuiListAppend(
    struct shabuiAst* list,
    struct shabuiAst* toAdd
)
{
    while (list->next)
    {
        list = list->next;
    }

    list->next = toAdd;
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
