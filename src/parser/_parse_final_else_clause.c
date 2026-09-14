
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 *
 *  typedef struct _ast_final_else_clause_t {
 *      ast_node_t node;
 *      struct _ast_function_body_t* function_body;
 *  } ast_final_else_clause_t;
 */
ast_final_else_clause_t* _parse_final_else_clause(parser_context_t* context) {

    ENTER;
    ast_final_else_clause_t* node = NULL;
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

            // parens are optional
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else {
                    parser_error(context, "expected a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (function_body = _parse_function_body(context))) {
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a function body");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_final_else_clause_t*)create_ast_node(AST_FINAL_ELSE_CLAUSE);
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
