
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  type_specifier
 *      : literal_type
 *      | compound_name
 *      ;
 *
 *  typedef struct _ast_type_specifier_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_type_specifier_t;
 */
ast_type_specifier_t* _parse_type_specifier(parser_context_t* context) {

    ENTER;
    ast_type_specifier_t* node = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_type(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE+1;
            } break;

            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_compound_name(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_type_specifier_t*)create_ast_node(AST_TYPE_SPECIFIER);
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

