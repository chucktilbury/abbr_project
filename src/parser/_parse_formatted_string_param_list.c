
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  formatted_string_param_list
 *      : '(' ( formatted_string_param_item, (',' formatted_string_param_item)* )? ')'
 *      ;
 *
 *  typedef struct _ast_formatted_string_param_list_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_formatted_string_param_list_t;
 */
ast_formatted_string_param_list_t* _parse_formatted_string_param_list(parser_context_t* context) {

    ENTER;
    ast_formatted_string_param_list_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // optional first item
            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_formatted_string_param_list(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE+2;
                }
                else
                    state = START_STATE+4;
            } break;

            // must have a ',' or a ')'
            case START_STATE+2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = START_STATE+3;
                }
                else {
                    parser_expect_error(context, "a ',' or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // must have an item
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_formatted_string_param_list(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE+2;
                }
                else {
                    parser_expect_error(context, "a string format parameter");
                    state = RETURN_ERROR;
                }
            } break;

            // must have a ')'
            case START_STATE+4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = START_STATE+1;
                }
                else {
                    parser_expect_error(context, "a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_formatted_string_param_list_t*)create_ast_node(AST_FORMATTED_STRING_PARAM_LIST);
                node->list = list;
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
