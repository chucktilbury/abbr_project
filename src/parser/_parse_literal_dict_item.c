
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  literal_dict_item
 *      : string_literal ':' const_value
 *      ;
 *
 *  typedef struct _ast_literal_dict_item_t {
 *      ast_node_t node;
 *      struct _ast_string_literal_t* literal_str;
 *      struct _ast_const_value_t* const_value;
 *  } ast_literal_dict_item_t;
 */
ast_literal_dict_item_t* _parse_literal_dict_item(parser_context_t* context) {

    ENTER;
    ast_literal_dict_item_t* node = NULL;
    ast_string_literal_t* literal_str = NULL;
    ast_const_value_t* const_value = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (literal_str = _parse_string_literal(context)))
                    state = START_STATE + 1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_COLON) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else {
                    parser_expect_error(context, "a ':'");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE + 2: {
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
                node = (ast_literal_dict_item_t*)create_ast_node(AST_LITERAL_DICT_ITEM);
                node->literal_str = literal_str;
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
