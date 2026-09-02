#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "expression.h"

// return -1 if token is not an operator
int precedence(ast_operator_t* node) {
    switch(node->oper) {
        case OPER_ADD:
        case OPER_SUB:
            return 5;
        case OPER_MUL:
        case OPER_DIV:
        case OPER_MOD:
            return 6;
        case OPER_POW:
            return 7;
        case OPER_UMINUS:
        case OPER_UPLUS:
        case OPER_NOT:
            return 8;
        case OPER_EQU:
        case OPER_NEQU:
            return 3;
        case OPER_LT:
        case OPER_GT:
        case OPER_LTE:
        case OPER_GTE:
            return 4;
        case OPER_AND:
            return 2;
        case OPER_OR:
            return 1;
        default:
            return -1; // not an operator
    }
}

// return 1 if right, 0 if left
int associativity(ast_operator_t* node) {
    switch(node->oper) {
        case OPER_POW:
        case OPER_UMINUS:
        case OPER_UPLUS:
        case OPER_NOT:
            return 1;
        default:
            return 0;
    }
}

ast_node_t* postfix_to_tree(ast_node_list_t* queue) {

    ast_node_list_t* stack = create_ast_node_list();

    int post = 0;
    ast_node_t* node = iterate_ast_node_list(queue, &post);
    do {
        if(node->type == AST_OPERATOR) {
            switch(((ast_operator_t*)node)->oper) {
                case OPER_ADD:
                case OPER_SUB:
                case OPER_MUL:
                case OPER_DIV:
                case OPER_MOD:
                case OPER_POW:
                case OPER_EQU:
                case OPER_NEQU:
                case OPER_LT:
                case OPER_GT:
                case OPER_LTE:
                case OPER_GTE:
                case OPER_AND:
                case OPER_OR: {
                    ast_operator_t* oper = (ast_operator_t*)node;
                    oper->right = pop_ast_node_list(stack);
                    oper->left = pop_ast_node_list(stack);
                    push_ast_node_list(stack, node);
                } break;
                case OPER_NOT:
                case OPER_UMINUS:
                case OPER_UPLUS: {
                    ast_operator_t* oper = (ast_operator_t*)node;
                    oper->left = pop_ast_node_list(stack);
                    push_ast_node_list(stack, node);
                } break;
                default:
                    fprintf(stderr, "unknown operator: %d", ((ast_operator_t*)node)->oper);
                    exit(1);
            }
        }
        else if(node->type == AST_VALUE) {
            push_ast_node_list(stack, node);
        }
        else {
            fprintf(stderr, "unknown operator type: %d\n", node->type);
            exit(1);
        }
        node = iterate_ast_node_list(queue, &post);
    } while(node != NULL);

    print_ast_node_list(stack);
    return stack->list[0];
}

ast_node_t* infix_to_tree(token_t* token_list) {

    ast_node_list_t* stack = create_ast_node_list();
    ast_node_list_t* queue = create_ast_node_list();
    token_t* tok;
    int flag = 0;

    for(int i = 0; token_list[i].text != NULL; i++) {
        tok = &token_list[i];
        if(tok->type == TOK_OPERAND) {
            ast_value_t* val = (ast_value_t*)create_ast_node(AST_VALUE);
            val->value = strtod(tok->text, NULL);
            append_ast_node_list(queue, (ast_node_t*)val);
            flag = 0;
        }
        else if(tok->type == TOK_LPAREN) {
            push_ast_node_list(stack, create_ast_node(AST_LPAREN));
            flag = 1;
        }
        else if(tok->type == TOK_RPAREN) {
            while(1) {
                ast_node_t* node = peek_ast_node_list(stack);
                if(node != NULL) {
                    if(node->type == AST_LPAREN) {
                        pop_ast_node_list(stack);
                        break;
                    }
                    else
                        append_ast_node_list(queue, pop_ast_node_list(stack));

                    if(peek_ast_node_list(stack) == NULL)
                        break;
                }
                else {
                    fprintf(stderr, "imbalanced parens!\n");
                    exit(1);
                }
            }
            flag = 0;
        }
        else {
            ast_operator_t* oper = (ast_operator_t*)create_ast_node(AST_OPERATOR);
            oper->is_unary = 0;
            switch(tok->type) {
                case TOK_ADD:
                    if(flag) {
                        oper->oper = OPER_UPLUS;
                        oper->is_unary = 1;
                    }
                    else {
                        oper->oper = OPER_ADD;
                    }
                    break;
                case TOK_SUB:
                    if(flag) {
                        oper->oper = OPER_UMINUS;
                        oper->is_unary = 1;
                    }
                    else {
                        oper->oper = OPER_SUB;
                    }
                    break;
                case TOK_NOT:
                    if(flag) {
                        oper->oper = OPER_NOT;
                        oper->is_unary = 1;
                    }
                    else {
                        fprintf(stderr, "the \"not\" operator must be unary\n");
                        exit(1);
                    }
                    break;
                case TOK_MUL:
                case TOK_DIV:
                case TOK_MOD:
                case TOK_POW:
                case TOK_EQU:
                case TOK_NEQU:
                case TOK_LT:
                case TOK_GT:
                case TOK_LTE:
                case TOK_GTE:
                case TOK_AND:
                case TOK_OR:
                    if(!flag) {
                        oper->oper = (oper_type_t)tok->type;
                    }
                    else {
                        fprintf(stderr, "invalid unary operator: %s\n", tok->text);
                        exit(1);
                    }
                    break;
                default:
                    fprintf(stderr, "unknow operator token: %s", tok->text);
                    exit(1);
            }

            while(1) {
                ast_operator_t* node = (ast_operator_t*)peek_ast_node_list(stack);
                if(node != NULL) {
                    if(node->node.type == AST_LPAREN)
                        break;
                    else if((precedence(node) > precedence(oper)) ||
                            (precedence(node) == precedence(oper) && !associativity(oper))) {
                        append_ast_node_list(queue, pop_ast_node_list(stack));
                    }
                    else
                        break;
                }
                else
                    break;
            }
            push_ast_node_list(stack, (ast_node_t*)oper);
            flag = 1;
        }
    }

    while(NULL != peek_ast_node_list(stack))
        append_ast_node_list(queue, pop_ast_node_list(stack));

    destroy_ast_node_list(stack);

    print_ast_node_list(queue);
    return postfix_to_tree(queue);
}
