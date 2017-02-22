#include <stdio.h>
#include "shabuiparser.h"
#include "shabuiAst.h"

void indent(int depth)
{
    for (int i = 0; i < depth; ++i)
    {
        printf(" ");
    }
}

void traverseShabuiAst(struct shabuiAst* root, int depth)
{
    if (!root)
    {
        return;
    }

    do
    {
        indent(depth);
        switch (root->nodeType)
        {
            case SB_NODE_STRING_LITERAL:
                printf("string =: \"%s\"\n", root->str);
                break;
            case SB_NODE_NUMBER:
                printf("number =: %d\n", root->value);
                break;
            case SB_NODE_VERSION:
                printf("version = %d\n", root->value);
                break;
            case SB_NODE_SHADER:
                printf("shader\n");
                break;
            default:
                printf("unknown\n");
                break;
        }

        if (root->lhs)
        {
            indent(depth); printf("lhs:\n");
            traverseShabuiAst(root->lhs, depth + 1);
        }

        if (root->rhs)
        {
            indent(depth); printf("rhs:\n");
            traverseShabuiAst(root->rhs, depth + 1);
        }

        root = root->next;

    } while(root);
}

int main(int argc, char **argv)
{
    shabuiparse();
    traverseShabuiAst(lastShabuiAst, 0);
    return 0;
}
