
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  class_body
 *      : '{' class_item+ '}'
 *      ;
 *
 *  typedef struct _ast_class_body_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_class_definition_t;
 */
ast_class_body_t* _parse_class_body(parser_context_t* context) {

    ENTER;
    ast_class_body_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LCURLY) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else {
                    parser_expect_error(context, "a '{' for a class body");
                    state = RETURN_ERROR;
                }
            } break;

            // require at least one class_item
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_class_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 2;
                }
                else {
                    parser_syntax_error(context, "class body requires at least one item");
                    state = RETURN_ERROR;
                }
            } break;

            // class_item_loop
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else if(NULL != (item = (ast_node_t*)_parse_class_item(context)))
                    append_ast_node_list(list, item); // no state change
                else {
                    parser_expect_error(context, "a class body item or a '}'");
                    state = RETURN_ERROR;
                }
            } break;


            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_class_body_t*)create_ast_node(AST_CLASS_BODY);
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

