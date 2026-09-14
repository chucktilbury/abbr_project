
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  array_reference
 *      : identifier array_parameters (array_parameters)*
 *      ;
 *
 *  typedef struct _ast_array_reference_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      ast_node_list_t* array_parameters;
 *  } ast_array_reference_t;
 */
ast_array_reference_t* _parse_array_reference(parser_context_t* context) {

    ENTER;
    ast_array_reference_t* node = NULL;
    ast_identifier_t* ident = NULL;
    ast_node_t* item = NULL;
    ast_node_list_t* list = NULL;


    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (ident = _parse_identifier(context)))
                    state = START_STATE + 1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            // one required
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_array_parameters(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = REPEAT_STATE;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // add to the list
            case REPEAT_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_array_parameters(context)))
                    append_ast_node_list(list, item);
                else
                    state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_array_reference_t*)create_ast_node(AST_ARRAY_REFERENCE);
                node->identifier = ident;
                node->array_parameters = list;
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
