
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 *
 *  typedef struct _ast_do_clause_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *      struct _ast_loop_body_t* loop_body;
 *  } ast_do_clause_t;
 */
ast_do_clause_t* _parse_do_clause(parser_context_t* context) {

    ENTER;
    ast_do_clause_t* node = NULL;
    ast_expression_t* expr = NULL;
    ast_loop_body_t* loop_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DO) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // loop body is required
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (loop_body = _parse_loop_body(context)))
                    state = START_STATE + 2;
                else {
                    parser_error(context, "expected a loop body");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_WHILE) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else {
                    parser_error(context, "expected a 'while' keyword");
                    state = RETURN_ERROR;
                }
            } break;

            // the expression is optional, if there are no parens, go to match.
            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 4;
                }
                else // no expression
                    state = RETURN_MATCH;
            } break;

            // the expression is optional, but the parens are present
            case START_STATE + 4: {
                TRACE_STATE;
                expr = _parse_expression(context); // NULL if it's a ')'
                state = START_STATE + 5;
            } break;

            case START_STATE + 5: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_do_clause_t*)create_ast_node(AST_DO_CLAUSE);
                node->expr = expr;
                node->loop_body = loop_body;
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
