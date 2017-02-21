#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shabuiAst.h"

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

    int stringLength = strlen(str);
    node->str = malloc((stringLength+1)*sizeof(char));
    strcpy(node->str, str);

    return node;
}

struct shabuiAst* shabuiMakeVersion(struct shabuiAst* versionNumber)
{
    struct shabuiAst *node = shabuiMakeEmptyNode(SB_NODE_VERSION);
    node->lhs = versionNumber;
    return node;
}
