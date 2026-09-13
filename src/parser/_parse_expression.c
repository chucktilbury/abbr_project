
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

// return -1 if token is not an operator
int precedence(ast_operator_t* node) {
    switch(node->oper) {
        case TOK_ADD:
        case TOK_SUB:
            return 5;
        case TOK_MUL:
        case TOK_DIV:
        case TOK_MOD:
            return 6;
        case TOK_POW:
            return 7;
        case TOK_UNARY_MINUS:
        case TOK_UNARY_PLUS:
        case TOK_NOT:
            return 8;
        case TOK_EQU:
        case TOK_NEQ:
            return 3;
        case TOK_LT:
        case TOK_GT:
        case TOK_LTE:
        case TOK_GTE:
            return 4;
        case TOK_AND:
            return 2;
        case TOK_OR:
            return 1;
        default:
            return -1; // not an operator
    }
}

bool is_operator(token_type_t type) {

    switch(type) {
        case TOK_ADD:
        case TOK_SUB:
        case TOK_MUL:
        case TOK_DIV:
        case TOK_MOD:
        case TOK_POW:
        case TOK_UNARY_MINUS:
        case TOK_UNARY_PLUS:
        case TOK_NOT:
        case TOK_EQU:
        case TOK_NEQ:
        case TOK_LT:
        case TOK_GT:
        case TOK_LTE:
        case TOK_GTE:
        case TOK_AND:
        case TOK_OR:
            return true;
        default:
            return false; // not an operator
    }
}

// return 1 if right, 0 if left
int associativity(ast_operator_t* node) {
    switch(node->oper) {
        case TOK_POW:
        case TOK_UNARY_MINUS:
        case TOK_UNARY_PLUS:
        case TOK_NOT:
            return 1;
        default:
            return 0;
    }
}

ast_node_t* postfix_to_tree(parser_context_t* context, ast_node_list_t* queue) {

    ast_node_list_t* stack = create_ast_node_list();

    int post = 0;
    ast_node_t* node = iterate_ast_node_list(queue, &post);
    do {
        if(node->type == AST_OPERATOR) {
            switch(((ast_operator_t*)node)->oper) {
                case TOK_ADD:
                case TOK_SUB:
                case TOK_MUL:
                case TOK_DIV:
                case TOK_MOD:
                case TOK_POW:
                case TOK_EQU:
                case TOK_NEQ:
                case TOK_LT:
                case TOK_GT:
                case TOK_LTE:
                case TOK_GTE:
                case TOK_AND:
                case TOK_OR: {
                    ast_operator_t* oper = (ast_operator_t*)node;
                    oper->right = pop_ast_node_list(stack);
                    oper->left = pop_ast_node_list(stack);
                    push_ast_node_list(stack, node);
                } break;
                case TOK_NOT:
                case TOK_UNARY_MINUS:
                case TOK_UNARY_PLUS: {
                    ast_operator_t* oper = (ast_operator_t*)node;
                    oper->left = pop_ast_node_list(stack);
                    push_ast_node_list(stack, node);
                } break;
                default:
                    parser_error(context, "expected an operator");
                    return NULL;
            }
        }
        else if(node->type == AST_PRIMARY_EXPRESSION) {
            push_ast_node_list(stack, node);
        }
        else {
            parser_error(context, "expected an operator");
            return NULL;
        }
        node = iterate_ast_node_list(queue, &post);
    } while(node != NULL);

    return stack->buffer[0];
}

ast_node_t* infix_to_tree(parser_context_t* context) {

    ast_node_list_t* stack = create_ast_node_list();
    ast_node_list_t* queue = create_ast_node_list();
    ast_primary_expression_t* value;
    ast_operator_t* oper;
    // token_t* tok;
    int flag = 0;
    bool finished = false;

    while(!finished) {
        // for(int i = 0; token_list[i].text != NULL; i++) {
        // tok = &token_list[i];
        if(NULL != (value = _parse_primary_expression(context))) {
            append_ast_node_list(queue, (ast_node_t*)value);
            flag = 0;
        }
        else if(TOKEN_TYPE == TOK_LPAREN) {
            // never gets to the output. this is a marker.
            oper = (ast_operator_t*)create_ast_node(AST_OPERATOR);
            oper->oper = TOKEN_TYPE;
            push_ast_node_list(stack, (ast_node_t*)oper);
            flag = 1;
        }
        else if(TOKEN_TYPE == TOK_RPAREN) {
            // don't create the node....
            while(1) {
                ast_node_t* node = peek_ast_node_list(stack);
                if(node != NULL) {
                    if(node->type == TOK_LPAREN) {
                        pop_ast_node_list(stack);
                        break;
                    }
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
        else if(is_operator(TOKEN_TYPE)) {
            ast_operator_t* oper = (ast_operator_t*)create_ast_node(AST_OPERATOR);
            oper->is_unary = 0;
            switch(TOKEN_TYPE) {
                case TOK_ADD:
                    if(flag) {
                        oper->oper = TOK_UNARY_PLUS;
                        oper->is_unary = 1;
                    }
                    else {
                        oper->oper = TOK_ADD;
                    }
                    break;
                case TOK_SUB:
                    if(flag) {
                        oper->oper = TOK_UNARY_MINUS;
                        oper->is_unary = 1;
                    }
                    else {
                        oper->oper = TOK_SUB;
                    }
                    break;
                case TOK_NOT:
                    if(flag) {
                        oper->oper = TOK_NOT;
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
                case TOK_NEQ:
                case TOK_LT:
                case TOK_GT:
                case TOK_LTE:
                case TOK_GTE:
                case TOK_AND:
                case TOK_OR:
                    if(!flag) {
                        oper->oper = TOKEN_TYPE;
                    }
                    else {
                        parser_error(context, "expected a unary operator");
                        return NULL;
                    }
                    break;
                default:
                    parser_error(context, "expected an arithmetic or a comparison operator");
                    return NULL;
            }

            while(1) {
                ast_operator_t* node = (ast_operator_t*)peek_ast_node_list(stack);
                if(node != NULL) {
                    if(node->oper == TOK_LPAREN)
                        break;

                    if((precedence(node) > precedence(oper)) ||
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
        else
            finished = true;
    }

    while(NULL != peek_ast_node_list(stack))
        append_ast_node_list(queue, pop_ast_node_list(stack));

    destroy_ast_node_list(stack);

    // print_ast_node_list(queue);
    return postfix_to_tree(context, queue);
}

/*
 *  expression
 *      : expression ('*' | '/' | '%') expression
 *      | expression '^' expression
 *      | expression ('+' | '-') expression
 *      | expression ('<' | '>' | '<=' | '>=' | 'lt' | 'gt' | 'lte' | 'gte') expression
 *      | expression ('==' | '!=' | 'equ' | 'neq' ) expression
 *      | expression ('&&' | 'and') expression
 *      | expression ('||' | 'or') expression
 *      | ('!' | 'not' | '-') expression
 *      | '(' expression ')'
 *      | primary_expression
 *      ;
 */
ast_expression_t* _parse_expression(parser_context_t* context) {

    ENTER;
    ast_expression_t* node = NULL;
    // ast elements here

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_expression_t*)create_ast_node(AST_EXPRESSION);
                // ast elements here
                flush_token_queue();
            } break;

            case RETURN_NO_MATCH: {
                TRACE_STATE;
                reset_token_queue();
            } break;

            case RETURN_ERROR: {
                TRACE_STATE;
                recover_parser_error(context);
            } break;

            default:
                FATAL("invalid state: %d", state);
        }
    }

    RETURN(node);
}
