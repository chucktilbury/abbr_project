
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 *
 *  typedef struct _ast_assignment_t {
 *      ast_node_t node;
 *      struct  _ast_compound_reference_t* compound_reference;
 *      struct  _ast_expression_t* expression;
 *  } ast_assignment_t;
 */
ast_assignment_t* _parse_assignment(parser_context_t* context) {

    ENTER;
    ast_assignment_t* node = NULL;
    ast_compound_reference_t* ref = NULL;
    ast_expression_t* expr = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (ref = _parse_compound_reference(context)))
                    state = START_STATE + 1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_ASSIGN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = RETURN_MATCH;
                else {
                    parser_error(context, "expected an expression");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_assignment_t*)create_ast_node(AST_ASSIGNMENT);
                node->compound_reference = ref;
                node->expression = expr;
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
