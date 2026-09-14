
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | break_statement
 *      | continue_statement
 *      | loop_body
 *      ;
 *
 *  typedef struct _ast_loop_body_item_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_loop_body_item_t;
 */
ast_loop_body_item_t* _parse_loop_body_item(parser_context_t* context) {

    ENTER;
    ast_loop_body_item_t* node = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_function_body_item(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_yield_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_break_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_continue_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 4;
            } break;

            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_loop_body(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_loop_body_item_t*)create_ast_node(AST_LOOP_BODY_ITEM);
                node->item = item;
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
