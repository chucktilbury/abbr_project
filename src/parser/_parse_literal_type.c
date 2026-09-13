
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  literal_type
 *      : ('integer' | 'int')
 *      | ('boolean' | 'bool')
 *      | 'string'
 *      | 'dict'
 *      | 'list'
 *      | 'unsigned'
 *      | 'float'
 *      | 'nothing'
 *      ;
 *
 *  typedef struct _ast_literal_type_t {
 *      ast_node_t node;
 *      token_type_t type;
 *  } ast_literal_type_t;
 */
ast_literal_type_t* _parse_literal_type(parser_context_t* context) {

    ENTER;
    ast_literal_type_t* node = NULL;
    token_type_t type;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_INTEGER) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_BOOL) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_STRING) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DICT) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 4;
            } break;

            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_ARRAY) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 5;
            } break;

            case START_STATE + 6: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_UNSIGNED) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 7;
            } break;

            case START_STATE + 7: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_FLOAT) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 8;
            } break;

            case START_STATE + 8: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_NOTHING) {
                    type = TOKEN_TYPE;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_literal_type_t*)create_ast_node(AST_LITERAL_TYPE);
                node->type = type;
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
