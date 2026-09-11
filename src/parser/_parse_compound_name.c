
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  compound_name
 *      : identifier ('.' identifier)*
 *      ;
 *
 *  typedef struct _ast_compound_name_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_compound_name_t;
 */
ast_compound_name_t* _parse_compound_name(parser_context_t* context) {

    ENTER;
    ast_compound_name_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_identifier(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // if there is a '.' after the identifier, then loop, otherwise match
            case START_STATE+1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DOT) {
                    consume_token();
                    state = REPEAT_STATE;
                }
                else
                    state = RETURN_MATCH;
            } break;

            case REPEAT_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_identifier(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE+1;
                }
                else {
                    parser_error(context, "expected an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_compound_name_t*)create_ast_node(AST_COMPOUND_NAME);
                node->list = list;
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

