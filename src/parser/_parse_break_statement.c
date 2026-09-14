
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  break_statement
 *      : 'break'
 *      ;
 *
 *  typedef struct _ast_break_statement_t {
 *      ast_node_t node;
 *  } ast_break_statement_t;
 */
ast_break_statement_t* _parse_break_statement(parser_context_t* context) {

    ENTER;
    ast_break_statement_t* node = NULL;
    // no ast elements

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_BREAK) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_break_statement_t*)create_ast_node(AST_BREAK_STATEMENT);
                // no ast elements
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
