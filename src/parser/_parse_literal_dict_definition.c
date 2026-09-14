
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  literal_dict_definition
 *      : '[' ( literal_dict_item (',' literal_dict_item)* )? ']'
 *      ;
 *
 *  typedef struct _ast_literal_dict_definition_t {
 *      ast_node_t node;
 *      ast_node_list_t* literal_dict_item;
 *  } ast_literal_dict_definition_t;
 */
ast_literal_dict_definition_t* _parse_literal_dict_definition(parser_context_t* context) {

    ENTER;
    ast_literal_dict_definition_t* node = NULL;
    ast_node_list_t* list;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            // required '['
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LSQUARE) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // first const value is optional
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_dict_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 2;
                }
                else
                    state = START_STATE + 4;
            } break;

            // expecting a ',' or a ']'
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RSQUARE) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else {
                    parser_error(context, "expected a ',' or a ']'");
                    state = RETURN_ERROR;
                }

            } break;

            // const value after a comma is required
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_literal_dict_item(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE + 2;
                }
                else {
                    parser_error(context, "expected a constant value");
                    state = RETURN_ERROR;
                }
            } break;

            // required ']'
            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RSQUARE) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a ']'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_literal_dict_definition_t*)create_ast_node(AST_LITERAL_DICT_DEFINITION);
                node->literal_dict_item = list;
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
