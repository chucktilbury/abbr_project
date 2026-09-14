
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_declaration
 *      : type_specifier identifier function_declaration_parameters function_body?
 *      ;
 *
 *  typedef struct _ast_function_declaration_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_function_declaration_parameters_t* function_declaration_parameters;
 *      struct _ast_function_body_t* func_body;
 *  } ast_function_declaration_t;
 *
 */
ast_function_declaration_t* _parse_function_declaration(parser_context_t* context) {

    ENTER;
    ast_function_declaration_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_function_declaration_parameters_t* function_declaration_parameters = NULL;
    ast_function_body_t* func_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (type_specifier = _parse_type_specifier(context)))
                    state = START_STATE + 1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = START_STATE + 2;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (function_declaration_parameters = _parse_function_declaration_parameters(context)))
                    state = START_STATE + 3;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                func_body = _parse_function_body(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_declaration_t*)create_ast_node(AST_FUNCTION_DECLARATION);
                node->identifier = identifier;
                node->type_specifier = type_specifier;
                node->function_declaration_parameters = function_declaration_parameters;
                node->func_body = func_body;
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
