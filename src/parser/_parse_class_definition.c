
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  class_definition
 *      : 'class' identifier ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
 *      ;
 *
 *  typedef struct _ast_class_definition_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      ast_node_list_t* i_list;
 *      ast_node_list_t* c_list;
 *  } ast_class_definition_t;
 */
ast_class_definition_t* _parse_class_definition(parser_context_t* context) {

    ENTER;
    ast_class_definition_t* node = NULL;
    ast_identifier_t* ident = NULL;
    ast_node_list_t* ilist = NULL;
    ast_node_list_t* clist = NULL;
    ast_node_t* item;
    symbol_t* symbol = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_CLASS) {
                    consume_token();
                    state = START_STATE + 10;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required identifier
            case START_STATE + 10: {
                TRACE_STATE;
                if(NULL != (ident = _parse_identifier(context)))
                    state = USER_STATE;
                else {
                    parser_expect_error(context, "an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            /////////// optional inheritance list ///////////////
            // optional left paren. If not, then skip the inheritance list
            case USER_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = USER_STATE + 100;
                }
                else
                    state = USER_STATE + 500;
            } break;

            // optional first inheritance item
            case USER_STATE + 100: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_inheritance_item(context))) {
                    ilist = create_ast_node_list();
                    append_ast_node_list(ilist, item);
                    state = USER_STATE + 120; // expect a comma or a rparen
                }
                else
                    state = USER_STATE + 110; // expect a ')'
            } break;

            // require a ')' after no inheritance item
            case USER_STATE + 110: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = USER_STATE + 500;
                }
                else {
                    parser_expect_error(context, "a type name, a symbol, a ',', or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // require an inheritance item loop after the comma
            case USER_STATE + 200: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_inheritance_item(context))) {
                    append_ast_node_list(ilist, item);
                    state = USER_STATE + 210;
                }
                else {
                    parser_expect_error(context, "a type name or a symbol");
                    state = RETURN_ERROR;
                }
            } break;

            // require a comma or a right paren after an inheritance item in loop
            case USER_STATE + 120: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = USER_STATE + 200;
                }
                else if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = USER_STATE + 500; // get the class body
                }
                else {
                    parser_expect_error(context, "a ',' or a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            ///////////// class body ///////////////////
            // required '{'
            case USER_STATE + 500: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LCURLY) {
                    consume_token();
                    state = USER_STATE + 600;
                }
                else {
                    parser_expect_error(context, "a '{' for a class body");
                    state = RETURN_ERROR;
                }
            } break;

            // require at least one class_item
            case USER_STATE + 600: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_class_item(context))) {
                    clist = create_ast_node_list();
                    append_ast_node_list(clist, item);
                    state = USER_STATE + 610;
                }
                else {
                    parser_syntax_error(context, "class body requires at least one item");
                    state = RETURN_ERROR;
                }
            } break;

            // class_item_loop
            case USER_STATE + 610: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else if(NULL != (item = (ast_node_t*)_parse_class_item(context)))
                    append_ast_node_list(clist, item); // no state change
                else {
                    parser_expect_error(context, "a class body item or a '}'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_class_definition_t*)create_ast_node(AST_CLASS_DEFINITION);
                node->identifier = ident;
                node->i_list = ilist;
                node->c_list = clist;
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
