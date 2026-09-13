
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 *
 *  typedef struct _ast_formatted_string_t {
 *      ast_node_t node;
 *      string_t* literal_str;
 *      ast_node_list_t* list;
 *  } ast_formatted_string_t;
 */
ast_formatted_string_t* _parse_formatted_string(parser_context_t* context) {

    ENTER;
    ast_formatted_string_t* node = NULL;
    string_t* literal_str = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_DSTR) {
                    literal_str = copy_string(get_token()->text);
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else
                    state = RETURN_MATCH;
            } break;

            // the first expression is optional
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_expression(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = REPEAT_STATE;
                }
                else
                    state = START_STATE + 2; // no expressions, just the '()'
            } break;

            // required ')'
            case START_STATE + 2: {
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

            // a ',' is required between expressions
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
                if(NULL != (item = (ast_node_t*)_parse_expression(context))) {
                    append_ast_node_list(list, item);
                    state = REPEAT_STATE;
                }
                else {
                    parser_error(context, "expected an expression");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_formatted_string_t*)create_ast_node(AST_FORMATTED_STRING);
                node->literal_str = literal_str;
                node->list = list;
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
