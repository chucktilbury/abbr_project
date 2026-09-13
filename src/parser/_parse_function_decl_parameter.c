
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_decl_parameter
 *      : type_specifier (identifier)?
 *      ;
 *
 *  typedef struct _ast_function_decl_parameter_t {
 *      ast_node_t node;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_identifier_t* identifier;
 *  } ast_function_decl_parameter_t;
 */
ast_function_decl_parameter_t* _parse_function_decl_parameter(parser_context_t* context) {

    ENTER;
    ast_function_decl_parameter_t* node = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_identifier_t* identifier = NULL;

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

            // optional identifier
            case START_STATE + 1: {
                TRACE_STATE;
                identifier = _parse_identifier(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_decl_parameter_t*)create_ast_node(AST_FUNCTION_DECL_PARAMETER);
                node->type_specifier = type_specifier;
                node->identifier = identifier;
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
