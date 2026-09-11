
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  compound_reference_item
 *      : identifier
 *      | function_reference
 *      | array_reference
 *      ;
 *
 *  typedef struct _ast_compound_reference_item_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_compound_reference_item_t;
 */
ast_compound_reference_item_t* _parse_compound_reference_item(parser_context_t* context) {

    ENTER;
    ast_compound_reference_item_t* node = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_identifier(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE+1;
            } break;

            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_function_reference(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE+2;
            } break;

            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_array_reference(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_compound_reference_item_t*)create_ast_node(AST_COMPOUND_REFERENCE_ITEM);
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

