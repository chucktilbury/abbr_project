
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  global_scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 *
 *  typedef struct _ast_global_scope_operator_t {
 *      ast_node_t node;
 *      token_type_t tok;
 *  } ast_global_scope_operator_t;
 */
ast_global_scope_operator_t* _parse_global_scope_operator(parser_context_t* context) {

    ENTER;
    ast_global_scope_operator_t* node = NULL;
    token_type_t tok;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_PUBLIC || TOKEN_TYPE == TOK_PRIVATE) {
                    tok = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_global_scope_operator_t*)create_ast_node(AST_GLOBAL_SCOPE_OPERATOR);
                node->tok = tok;
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

