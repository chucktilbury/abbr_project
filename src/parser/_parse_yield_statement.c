
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 *
 *  typedef struct _ast_yield_statement_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *  } ast_yield_statement_t;
 */
ast_yield_statement_t* _parse_yield_statement(parser_context_t* context) {

    ENTER;
    ast_yield_statement_t* node = NULL;
    ast_expression_t* expr = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_YIELD) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = START_STATE + 3;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_yield_statement_t*)create_ast_node(AST_YIELD_STATEMENT);
                node->expr = expr;
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
