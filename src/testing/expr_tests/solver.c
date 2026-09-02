
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ast_node.h"

#define LNODE(n) (((n)->type == AST_OPERATOR)? ((ast_operator_t*)(n))->left: NULL)
#define RNODE(n) (((n)->type == AST_OPERATOR)? ((ast_operator_t*)(n))->right: NULL)

static void _composer(ast_node_t* node) {

    if(node == NULL)
        return;

    if(node->type == AST_VALUE) {
        printf("%0.3f", ((ast_value_t*)node)->value);
    }
    else if(node->type == AST_OPERATOR) {
        printf("(");

        switch(((ast_operator_t*)node)->oper) {
            case OPER_ADD:
                _composer(LNODE(node));
                printf("+");
                _composer(RNODE(node));
                break;
            case OPER_SUB:
                _composer(LNODE(node));
                printf("-");
                _composer(RNODE(node));
                break;
            case OPER_MUL:
                _composer(LNODE(node));
                printf("*");
                _composer(RNODE(node));
                break;
            case OPER_DIV:
                _composer(LNODE(node));
                printf("/");
                _composer(RNODE(node));
                break;
            case OPER_UMINUS:
                printf("-");
                _composer(LNODE(node));
                break;
            case OPER_UPLUS:
                printf("+");
                _composer(LNODE(node));
                break;
            case OPER_MOD:
                printf("remainderf(");
                _composer(LNODE(node));
                printf(",");
                _composer(RNODE(node));
                printf(")");
                break;
            case OPER_POW:
                printf("powf(");
                _composer(LNODE(node));
                printf(",");
                _composer(RNODE(node));
                printf(")");
                break;
            default:
                fprintf(stderr, "unhandled case in %s\n", __PRETTY_FUNCTION__);
                exit(1);
        }
        printf(")");
    }
}

void composer(ast_node_t* node) {

    printf("\n");
    _composer(node);
    printf("\n");
}

float solver(ast_node_t* node) {

    float result = 0.0;

    if(node->type == AST_VALUE) {
        result = ((ast_value_t*)node)->value;
    }
    else if(node->type == AST_OPERATOR) {
        float left, right;
        if(LNODE(node) != NULL)
            left = solver(LNODE(node));
        if(RNODE(node) != NULL)
            right = solver(RNODE(node));

        switch(((ast_operator_t*)node)->oper) {
            case OPER_ADD:    result = left + right;  break;
            case OPER_SUB:    result = left - right;  break;
            case OPER_MUL:    result = left * right;  break;
            case OPER_DIV:    result = left / right;  break;
            case OPER_UMINUS: result = -left;         break;
            case OPER_UPLUS:  result = +left;         break;
            case OPER_MOD:    result = remainderf(left, right); break;
            case OPER_POW:    result = powf(left, right); break;
            default:
                fprintf(stderr, "unhandled case in %s\n", __PRETTY_FUNCTION__);
                exit(1);
        }
    }

    return result;
}

