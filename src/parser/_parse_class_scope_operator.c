
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  class_scope_operator
 *      : 'public'
 *      | 'private'
 *      | 'protected'
 *      ;
 *
 *  typedef struct _ast_class_scope_operator_t {
 *      ast_node_t node;
 *      token_type_t tok;
 *  } ast_class_scope_operator_t;
 */
ast_class_scope_operator_t* _parse_class_scope_operator(parser_context_t* context) {

    ENTER;
    ast_class_scope_operator_t* node = NULL;
    token_type_t type;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_PUBLIC) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_PRIVATE) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_PROTECTED) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_class_scope_operator_t*)create_ast_node(AST_CLASS_SCOPE_OPERATOR);
                node->tok = type;
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
