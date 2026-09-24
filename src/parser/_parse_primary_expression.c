
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  primary_expression
 *      : literal_number
 *      | literal_string
 *      | compound_reference
 *      ;
 *
 *  typedef struct _ast_primary_expression_t {
 *      ast_node_t node;
 *      ast_node_t* value;
 *  } ast_primary_expression_t;
 */
ast_primary_expression_t* _parse_primary_expression(parser_context_t* context) {

    ENTER;
    ast_primary_expression_t* node = NULL;
    ast_node_t* value = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (value = (ast_node_t*)_parse_literal_number(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (value = (ast_node_t*)_parse_literal_string(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (value = (ast_node_t*)_parse_compound_reference(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 3;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (value = (ast_node_t*)_parse_type_cast(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 4;
            } break;

            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (value = (ast_node_t*)_parse_type_of(context)))
                    state = RETURN_MATCH;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_primary_expression_t*)create_ast_node(AST_PRIMARY_EXPRESSION);
                node->value = value;
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
