
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  const_value
 *      : literal_number
 *      | string_literal
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 *
 *  typedef struct _ast_const_value_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_const_value_t;
 */
ast_const_value_t* _parse_const_value(parser_context_t* context) {

    ENTER;
    ast_const_value_t* node = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_number(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_string_literal(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_array_definition(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_dict_definition(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_const_value_t*)create_ast_node(AST_CONST_VALUE);
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
