
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  continue_statement
 *      : 'continue'
 *      ;
 *
 *  typedef struct _ast_continue_statement_t {
 *      ast_node_t node;
 *  } ast_continue_statement_t;
 */
ast_continue_statement_t* _parse_continue_statement(parser_context_t* context) {

    ENTER;
    ast_continue_statement_t* node = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_CONTINUE) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_continue_statement_t*)create_ast_node(AST_CONTINUE_STATEMENT);
                // no ast elements
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
