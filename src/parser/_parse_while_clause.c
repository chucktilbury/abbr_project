
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 *
 *  typedef struct _ast_while_clause_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *      struct _ast_loop_body_t* loop_body;
 *  } ast_while_clause_t;
 */
ast_while_clause_t* _parse_while_clause(parser_context_t* context) {

    ENTER;
    ast_while_clause_t* node = NULL;
    ast_expression_t* expr = NULL;
    ast_loop_body_t* loop_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_WHILE) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // optional '('
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else
                    state = START_STATE + 4;
            } break;

            // if the optional '(' is present, then optional expression
            case START_STATE + 2: {
                TRACE_STATE;
                expr = _parse_expression(context);
                state = START_STATE + 3;
            } break;

            // required ')'
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

            // required loop body
            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (loop_body = _parse_loop_body(context)))
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a loop body");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_while_clause_t*)create_ast_node(AST_WHILE_CLAUSE);
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
