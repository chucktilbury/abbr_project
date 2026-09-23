
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  namespace
 *      : 'namespace' identifier '{' namespace_item* '}'
 *      ;
 *
 *  typedef struct _ast_namespace_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      ast_node_list_t* list;
 *  } ast_namespace_t;
 */
ast_namespace_t* _parse_namespace(parser_context_t* context) {

    ENTER;
    ast_namespace_t* node = NULL;
    ast_identifier_t* identifier;
    ast_node_list_t* list;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_NAMESPACE) {
                    consume_token();
                    state = START_STATE + 1;
                }
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

            // required '{'
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LCURLY) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else {
                    parser_expect_error(context, "a '{'");
                    state = RETURN_ERROR;
                }
            } break;

            // first namespace_item
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_namespace_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 4;
                }
                else
                    state = START_STATE + 6;
            } break;

            // optional '}'
            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else
                    state = START_STATE + 5;
            } break;

            // required namespace_item
            case START_STATE + 5: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_namespace_item(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE + 4;
                }
                else {
                    parser_expect_error(context, "a valid namespace item");
                    state = RETURN_ERROR;
                }
            } break;

            // required '}'
            case START_STATE + 6: {
                TRACE_STATE;
                TRACE_TOKEN;
                if(TOKEN_TYPE == TOK_RCURLY) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_expect_error(context, "a '}'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_namespace_t*)create_ast_node(AST_NAMESPACE);
                node->identifier = identifier;
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
