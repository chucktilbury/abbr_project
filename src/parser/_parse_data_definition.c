
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  data_definition
 *      : type_specifier identifier ( '=' expression )?
 *      ;
 *
 *  typedef struct _ast_data_definition_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_expression_t* expression;
 *  } ast_data_definition_t;
 */
ast_data_definition_t* _parse_data_definition(parser_context_t* context) {

    ENTER;
    ast_data_definition_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_expression_t* expression = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (type_specifier = _parse_type_specifier(context)))
                    state = START_STATE+1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = START_STATE+2;
                else {
                    parser_error(context, "expected an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            // assignment is optional
            case START_STATE+2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_ASSIGN) {
                    consume_token();
                    state = START_STATE+3;
                }
                else
                    state = RETURN_MATCH;
            } break;

            // if we saw a '=' we need the expression...
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (expression = _parse_expression(context)))
                    state = RETURN_MATCH;
                else {
                    parser_error(context, "expected an expression");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_data_definition_t*)create_ast_node(AST_DATA_DEFINITION);
                node->identifier = identifier;
                node->type_specifier = type_specifier;
                node->expression = expression;
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

