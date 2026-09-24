
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  inheritance_list
 *      : '(' (inheritance_item (',' inheritance_item)*)? ')'
 *      ;
 *
 *  typedef struct _ast_inheritance_list_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_inheritance_list_t;
 */
ast_inheritance_list_t* _parse_inheritance_list(parser_context_t* context) {

    ENTER;
    ast_inheritance_list_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // optional first inheritance item
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_inheritance_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 4; // expect a comma or a rparen
                }
                else
                    state = START_STATE + 2; // expect a ')'
            } break;

            // require a ')' after no inheritance item
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    // leave the marker as NULL, since there is nothing in the list
                    state = RETURN_NO_MATCH; 
                }
                else {
                    parser_expect_error(context, "a type name, a symbol, or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // require an inheritance item loop after the comma
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_inheritance_item(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE + 4;
                }
                else {
                    parser_expect_error(context, "a type name or a symbol");
                    state = RETURN_ERROR;
                }
            } break;

            // require a comma or a right paren after an inheritance item in loop
            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_expect_error(context, "a ',' or a ')'");
                    state = RETURN_ERROR;
                }
            } break;


            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_inheritance_list_t*)create_ast_node(AST_INHERITANCE_LIST);
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

