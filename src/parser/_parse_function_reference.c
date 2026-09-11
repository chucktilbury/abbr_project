
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  function_reference
 *      : identifier '(' ( expression (',' expression)* )? ')'
 *      ;
 *
 *  typedef struct _ast_function_reference_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      ast_node_list_t* expr;
 *  } ast_function_reference_t;
 */
ast_function_reference_t* _parse_function_reference(parser_context_t* context) {

    ENTER;
    ast_function_reference_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = START_STATE+1;
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required left paren
            case START_STATE+1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE+2;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // first expression
            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_expression(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE+3;
                }
                else
                    state = START_STATE+5;
            } break;

            // looking for a ',' or a ')'
            case START_STATE+3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_COMMA) {
                    consume_token();
                    state = START_STATE+4;
                }
                else if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a ')' or a ','");
                    state = RETURN_ERROR;
                }
            } break;

            // get another expression
            case START_STATE+4: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_expression(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE+3;
                }
                else {
                    parser_error(context, "expected an expression");
                    state = RETURN_ERROR;
                }
            } break;

            // required ending right paren for empty parens
            case START_STATE+5: {
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
                node = (ast_function_reference_t*)create_ast_node(AST_FUNCTION_REFERENCE);
                node->identifier = identifier;
                node->expr = list;
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

