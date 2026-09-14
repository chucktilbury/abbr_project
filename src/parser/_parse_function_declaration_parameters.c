
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 *
 *  typedef struct _ast_function_declaration_parameters_t {
 *      ast_node_t node;
 *      ast_node_list_t* item;
 *  } ast_function_declaration_parameters_t;
 */
ast_function_declaration_parameters_t* _parse_function_declaration_parameters(parser_context_t* context) {

    ENTER;
    ast_function_declaration_parameters_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_function_decl_parameter_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            // the '()' are required the list is optional
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // first one...
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = _parse_function_decl_parameter(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, (ast_node_t*)item);
                    state = REPEAT_STATE;
                }
                else
                    state = RETURN_MATCH;
            } break;

            // required comma between parameters or a ')' to end the list
            case REPEAT_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = REPEAT_STATE + 1;
                }
                else if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a ',' or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case REPEAT_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = _parse_function_decl_parameter(context))) {
                    append_ast_node_list(list, (ast_node_t*)item);
                    state = REPEAT_STATE;
                }
                else {
                    parser_error(context, "expected a function declaration parameter");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_function_declaration_parameters_t*)create_ast_node(AST_FUNCTION_DECLARATION_PARAMETERS);
                node->item = list;
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
