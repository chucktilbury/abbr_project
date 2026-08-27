
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  const_value
 *      : LITERAL_INT
 *      | LITERAL_UNS
 *      | LITERAL_FLOAT
 *      | LITERAL_SSTR
 *      | LITERAL_DSTR
 *      | LITERAL_BOOL
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 */
ast_const_value_t* _parse_const_value(parser_context_t* context) {

    ENTER;
    ast_const_value_t* node = NULL;
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
                node = (ast_const_value_t*)create_ast_node(AST_CONST_VALUE);
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

