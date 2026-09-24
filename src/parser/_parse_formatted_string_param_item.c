
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  formatted_string
 *      : LITERAL_DSTR formatted_string_param_list?
 *      ;
 *
 *  typedef struct _ast_formatted_string_t {
 *      ast_node_t node;
 *      string_t* literal_str;
 *      ast_formatted_string_param_list_t* params;
 *  } ast_formatted_string_t;
 */
ast_formatted_string_t* _parse_formatted_string(parser_context_t* context) {

    ENTER;
    ast_formatted_string_t* node = NULL;
    string_t* literal_str = NULL;
    ast_formatted_string_param_list_t* params = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_DSTR) {
                    literal_str = copy_string(get_token()->text);
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                params = _parse_formatted_string_param_list(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_formatted_string_t*)create_ast_node(AST_FORMATTED_STRING);
                node->literal_str = literal_str;
                node->params = params;
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

