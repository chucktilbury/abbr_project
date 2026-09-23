
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  data_declaration
 *      : type_specifier identifier ( '=' const_value )?
 *      ;
 *
 *  typedef struct _ast_data_declaration_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_const_value_t* const_value;
 *  } ast_data_declaration_t;
 */
ast_data_declaration_t* _parse_data_declaration(parser_context_t* context) {

    ENTER;
    ast_data_declaration_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_const_value_t* const_value = NULL;

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
                else {
                    parser_expect_error(context, "an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_ASSIGN) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else
                    state = RETURN_MATCH;
            } break;

            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (const_value = _parse_const_value(context)))
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a constant value");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_data_declaration_t*)create_ast_node(AST_DATA_DECLARATION);
                node->identifier = identifier;
                node->type_specifier = type_specifier;
                node->const_value = const_value;
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
