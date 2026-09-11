
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  constructor_definition
 *      : identifier '.' 'create' function_definition_parameters function_body
 *      ;
 *
 *  typedef struct _ast_constructor_definition_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* group;
 *      struct _ast_function_definition_parameters_t* function_definition_parameters;
 *      struct _ast_function_body_t* function_body;
 *  } ast_constructor_definition_t;
 */
ast_constructor_definition_t* _parse_constructor_definition(parser_context_t* context) {

    ENTER;
    ast_constructor_definition_t* node = NULL;
    ast_identifier_t* group = NULL;
    ast_function_definition_parameters_t* parms = NULL;
    ast_function_body_t* body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (group = _parse_identifier(context)))
                    state = START_STATE+1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE+1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DOT) {
                    consume_token();
                    state = START_STATE+2;
                }
                else // could be something else....
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (parms = _parse_function_definition_parameters(context)))
                    state = START_STATE+3;
                else // could be a compound name or something else
                    state = RETURN_NO_MATCH;
            } break;

            // function body is required now....
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (body = _parse_function_body(context)))
                    state = RETURN_MATCH;
                else {
                    parser_error(context, "expected a function body");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_constructor_definition_t*)create_ast_node(AST_CONSTRUCTOR_DEFINITION);
                node->group = group;
                node->function_definition_parameters = parms;
                node->function_body = body;
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

