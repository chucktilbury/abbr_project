
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 *
 *  typedef struct _ast_if_clause_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *      struct _ast_function_body_t* function_body;
 *      struct _ast_final_else_clause_t* final_else_clause;
 *      ast_node_list_t* else_clause;
 *  } ast_if_clause_t;
 */
ast_if_clause_t* _parse_if_clause(parser_context_t* context) {

    ENTER;
    ast_if_clause_t* node = NULL;
    ast_expression_t* expr = NULL;
    ast_function_body_t* function_body = NULL;
    ast_final_else_clause_t* final_else_clause = NULL;
    ast_node_list_t* list;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_IF) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required left paren
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else {
                    parser_error(context, "expected a '('");
                    state = RETURN_ERROR;
                }
            } break;

            // required expression
            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = START_STATE + 3;
                else {
                    parser_error(context, "expected an expression");
                    state = RETURN_ERROR;
                }
            } break;

            // required right paren
            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = START_STATE + 4;
                }
                else {
                    parser_error(context, "expected a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // required function body
            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (function_body = _parse_function_body(context)))
                    state = START_STATE + 5;
                else {
                    parser_error(context, "expected a function body");
                    state = RETURN_ERROR;
                }
            } break;

            // optional zero or more else clauses
            // first one
            case START_STATE + 5: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_else_clause(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 6;
                }
                else
                    state = START_STATE + 7;
            } break;

            // check for another one
            case START_STATE + 6: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_else_clause(context))) {
                    append_ast_node_list(list, item);
                    // no state change
                }
                else
                    state = START_STATE + 7;
            } break;

            // optional final else clause
            case START_STATE + 7: {
                TRACE_STATE;
                final_else_clause = _parse_final_else_clause(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_if_clause_t*)create_ast_node(AST_IF_CLAUSE);
                node->expr = expr;
                node->function_body = function_body;
                node->final_else_clause = final_else_clause;
                node->else_clause = list;
                flush_token_queue();
                finished = true;
            } break;

            case RETURN_NO_MATCH: {
                TRACE_STATE;
                reset_token_queue();
                finished = true;
            } break;

            case RETURN_ERROR: {
                TRACE_STATE;
                recover_parser_error(context);
                finished = true;
            } break;

            default:
                FATAL("invalid state: %d", state);
        }
    }

    RETURN(node);
}
