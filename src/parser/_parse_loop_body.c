
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  loop_body
 *      : '{' loop_body_item* '}'
 *      ;
 *
 *  typedef struct _ast_loop_body_t {
 *      ast_node_t node;
 *      ast_node_list_t* item;
 *  } ast_loop_body_t;
 */
ast_loop_body_t* _parse_loop_body(parser_context_t* context) {

    ENTER;
    ast_loop_body_t* node = NULL;
    ast_node_list_t* list;
    ast_loop_body_item_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            // required '{'
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LCURLY) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // first item is optional
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = _parse_loop_body_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, (ast_node_t*)item);
                    state = START_STATE + 2;
                }
                else
                    state = START_STATE + 4;
            } break;

            // look for an optional '}'
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 3;
            } break;

            // get another required item
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = _parse_loop_body_item(context))) {
                    append_ast_node_list(list, (ast_node_t*)item);
                    state = START_STATE + 2;
                }
                else {
                    parser_error(context, "expected a loop body item");
                    state = RETURN_ERROR;
                }
            } break;

            // required '}'
            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a '}'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_loop_body_t*)create_ast_node(AST_LOOP_BODY);
                node->item = list;
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
