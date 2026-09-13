
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 *
 *  typedef struct _ast_literal_string_t {
 *      ast_node_t node;
 *      string_t* literal_str;
 *      struct _ast_formatted_string_t* formatted_string;
 *  } ast_literal_string_t;
 */
ast_literal_string_t* _parse_literal_string(parser_context_t* context) {

    ENTER;
    ast_literal_string_t* node = NULL;
    string_t* lstr = NULL;
    ast_formatted_string_t* fstr = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_SSTR) {
                    lstr = copy_string(get_token()->text);
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (fstr = _parse_formatted_string(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            }

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_literal_string_t*)create_ast_node(AST_LITERAL_STRING);
                node->literal_str = lstr;
                node->formatted_string = fstr;
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
