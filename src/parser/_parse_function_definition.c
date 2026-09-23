
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_definition
 *      : type_specifier identifier '.' identifier function_definition_parameters function_body
 *      ;
 *
 *  typedef struct _ast_function_definition_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* group;
 *      struct _ast_identifier_t* name;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_function_definition_parameters_t* function_definition_parameters;
 *      struct _ast_function_body_t* function_body;
 *  } ast_function_definition_t;
 */
ast_function_definition_t* _parse_function_definition(parser_context_t* context) {

    ENTER;
    ast_function_definition_t* node = NULL;
    ast_identifier_t* group = NULL;
    ast_identifier_t* name = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_function_definition_parameters_t* function_definition_parameters = NULL;
    ast_function_body_t* function_body = NULL;

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
                if(NULL != (group = _parse_identifier(context)))
                    state = START_STATE + 2;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DOT) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (name = _parse_identifier(context)))
                    state = START_STATE + 4;
                else
                    state = RETURN_NO_MATCH;
            } break;

            // still could be a data definition
            case START_STATE + 4: {
                TRACE_STATE;
                if(NULL != (function_definition_parameters = _parse_function_definition_parameters(context)))
                    state = START_STATE + 5;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 5: {
                TRACE_STATE;
                if(NULL != (function_body = _parse_function_body(context)))
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a function body");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_definition_t*)create_ast_node(AST_FUNCTION_DEFINITION);
                node->group = group;
                node->name = name;
                node->type_specifier = type_specifier;
                node->function_definition_parameters = function_definition_parameters;
                node->function_body = function_body;
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
