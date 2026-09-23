
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 *
 *  typedef struct _ast_else_clause_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *      struct _ast_function_body_t* function_body;
 *  } ast_else_clause_t;
 *
 *  NOTE: Parse for this before the final else clause.
 */
ast_else_clause_t* _parse_else_clause(parser_context_t* context) {

    ENTER;
    ast_else_clause_t* node = NULL;
    ast_expression_t* expr = NULL;
    ast_function_body_t* function_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_ELSE) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // could be trying to match a final_else, which does not require
            // the '(', however, this rule does require it.
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // still could be trying to match the final else clause
            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = START_STATE + 3;
                else
                    state = RETURN_NO_MATCH;
            } break;

            // At this point it must be a else that requires an expression and
            // a function body.
            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = START_STATE + 4;
                }
                else {
                    parser_expect_error(context, "a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // required function body
            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (function_body = _parse_function_body(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_else_clause_t*)create_ast_node(AST_ELSE_CLAUSE);
                node->expr = expr;
                node->function_body = function_body;
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
