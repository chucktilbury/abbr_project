
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_body
 *      : '{' function_body_item+ '}'
 *      ;
 *
 *  typedef struct _ast_function_body_t {
 *      ast_node_t node;
 *      ast_node_list_t* item;
 *  } ast_function_body_t;
 */
ast_function_body_t* _parse_function_body(parser_context_t* context) {

    ENTER;
    ast_function_body_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LCURLY) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // at least one item is required
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_function_body_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = REPEAT_STATE;
                }
                else
                    state = START_STATE + 2;
            } break;

            // check for a '}'
            case REPEAT_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = REPEAT_STATE + 1;
            } break;

            // else check for a required item
            case REPEAT_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_function_body_item(context))) {
                    append_ast_node_list(list, item);
                    state = REPEAT_STATE;
                }
                else {
                    parser_expect_error(context, "a function body item");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_body_t*)create_ast_node(AST_FUNCTION_BODY);
                node->item = list;
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
