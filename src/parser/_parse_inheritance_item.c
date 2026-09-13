
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 *
 *  typedef struct _ast_inheritance_item_t {
 *      ast_node_t node;
 *      struct _ast_compound_name_t* compound_name;
 *      struct _ast_class_scope_operator_t* class_scope_operator;
 *  } ast_inheritance_item_t;
 */
ast_inheritance_item_t* _parse_inheritance_item(parser_context_t* context) {

    ENTER;
    ast_inheritance_item_t* node = NULL;
    ast_compound_name_t* compound_name = NULL;
    ast_class_scope_operator_t* class_scope_operator = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                class_scope_operator = _parse_class_scope_operator(context);
                state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (compound_name = _parse_compound_name(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_inheritance_item_t*)create_ast_node(AST_INHERITANCE_ITEM);
                node->compound_name = compound_name;
                node->class_scope_operator = class_scope_operator;
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
