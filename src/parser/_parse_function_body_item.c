
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_body_item
 *      : compound_reference
 *      | assignment
 *      | data_definition
 *      | flow_statement
 *      | exit_statement
 *      | raise_statement
 *      | return_statement
 *      | inline_statement
 *      | function_body
 *      ;
 *
 *  typedef struct _ast_function_body_item_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_function_body_item_t;
 */
ast_function_body_item_t* _parse_function_body_item(parser_context_t* context) {

    ENTER;
    ast_function_body_item_t* node = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_compound_reference(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_assignment(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_data_definition(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_flow_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 4;
            } break;

            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_exit_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 5;
            } break;

            case START_STATE + 5: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_raise_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 6;
            } break;

            case START_STATE + 6: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_return_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 7;
            } break;

            case START_STATE + 7: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_inline_statement(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 8;
            } break;

            case START_STATE + 8: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_function_body(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_body_item_t*)create_ast_node(AST_FUNCTION_BODY_ITEM);
                node->item = item;
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
