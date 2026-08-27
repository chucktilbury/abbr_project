
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  literal_dict_item
 *      : (LITERAL_SSTR | LITERAL_DSTR) ':' const_value
 *      ;
 */
ast_literal_dict_item_t* _parse_literal_dict_item(parser_context_t* context) {

    ENTER;
    ast_literal_dict_item_t* node = NULL;
    // ast elements here

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_literal_dict_item_t*)create_ast_node(AST_LITERAL_DICT_ITEM);
                // ast elements here
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

