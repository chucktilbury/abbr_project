
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 *
 *  typedef struct _ast_function_definition_parameters_t {
 *      ast_node_t node;
 *      ast_node_list_t* data_declaration;
 *  } ast_function_definition_parameters_t;
 */
ast_function_definition_parameters_t* _parse_function_definition_parameters(parser_context_t* context) {

    ENTER;
    ast_function_definition_parameters_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            // parens are not optional
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // first decl is optional.
            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_data_declaration(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE+2;
                }
                else
                    state = START_STATE+4;
            } break;

            // looking for a ',' or a ')'
            case START_STATE+2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = START_STATE+3;
                }
                else {
                    parser_error(context, "expected a ',' or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // data decl required after a ','
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_data_declaration(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE+2;
                }
                else {
                    parser_error(context, "expected a data declaration");
                    state = RETURN_ERROR;
                }
            } break;

            // require an ending paren
            case START_STATE+4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_definition_parameters_t*)create_ast_node(AST_FUNCTION_DEFINITION_PARAMETERS);
                node->data_declaration = list;
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

