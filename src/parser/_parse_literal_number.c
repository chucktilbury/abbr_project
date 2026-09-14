
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  literal_number
 *      : LITERAL_INT
 *      | LITERAL_UNS
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      ;
 *
 *  typedef struct _ast_literal_number_t {
 *      ast_node_t node;
 *      token_type_t value_type;
 *      union {
 *          long inum;
 *          unsigned long unum;
 *          double fnum;
 *          unsigned char bnum;
 *      } value;
 *  } ast_literal_number_t;
 */
ast_literal_number_t* _parse_literal_number(parser_context_t* context) {

    ENTER;
    ast_literal_number_t* node = (ast_literal_number_t*)create_ast_node(AST_LITERAL_NUMBER);

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_INT) {
                    node->value_type = TOKEN_TYPE;
                    node->value.inum = strtol(raw_string(get_token()->text), NULL, 10);
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_UNS) {
                    node->value_type = TOKEN_TYPE;
                    node->value.unum = strtol(raw_string(get_token()->text), NULL, 16);
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_FLOAT) {
                    node->value_type = TOKEN_TYPE;
                    node->value.fnum = strtod(raw_string(get_token()->text), NULL);
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_TRUE) {
                    node->value_type = TOKEN_TYPE;
                    node->value.bnum = 1;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 4;
            } break;

            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_FALSE) {
                    node->value_type = TOKEN_TYPE;
                    node->value.bnum = 0;
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                flush_token_queue();
                finished = true;
            } break;

            case RETURN_NO_MATCH: {
                TRACE_STATE;
                _FREE(node);
                node = NULL;
                reset_token_queue();
                finished = true;
            } break;

            case RETURN_ERROR: {
                TRACE_STATE;
                _FREE(node);
                node = NULL;
                recover_parser_error(context);
                finished = true;
            } break;

            default:
                FATAL("invalid state: %d", state);
        }
    }

    RETURN(node);
}
