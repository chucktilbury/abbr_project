
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters function_body?
 *      ;
 *
 *  typedef struct _ast_constructor_declaration_t {
 *      ast_node_t node;
 *      struct _ast_function_declaration_parameters_t* function_declaration_parameters;
 *      struct _ast_function_body_t* func_body;
 *  } ast_constructor_declaration_t;
 */
ast_constructor_declaration_t* _parse_constructor_declaration(parser_context_t* context) {

    ENTER;
    ast_constructor_declaration_t* node = NULL;
    ast_function_declaration_parameters_t* parms = NULL;
    ast_function_body_t* body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_CREATE) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (parms = _parse_function_declaration_parameters(context)))
                    state = START_STATE + 2;
                else {
                    parser_error(context, "expected function parameter list");
                    state = RETURN_ERROR;
                }
            } break;

            // function body is optional
            case START_STATE + 2: {
                TRACE_STATE;
                body = _parse_function_body(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_constructor_declaration_t*)create_ast_node(AST_CONSTRUCTOR_DECLARATION);
                node->function_declaration_parameters = parms;
                node->func_body = body;
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
