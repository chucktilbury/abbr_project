
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? identifier)? )? ')' )? loop_body
 *      ;
 *
 *  typedef struct _ast_for_clause_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      struct _ast_expression_t* expr;
 *      struct _ast_type_specifier_t* type_specifier;
 *      struct _ast_loop_body_t* loop_body;
 *  } ast_for_clause_t;
 */
ast_for_clause_t* _parse_for_clause(parser_context_t* context) {

    ENTER;
    ast_for_clause_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_expression_t* expr = NULL;
    ast_type_specifier_t* type_specifier = NULL;
    ast_loop_body_t* loop_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_FOR) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // expression and parens are optional
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = USER_STATE;
                }
                else
                    state = USER_STATE + 100; // skip to the loop body
            } break;

            // if left paren is present then the expression is optional
            case USER_STATE: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = USER_STATE + 10; // look for an 'as' keyword
                else
                    state = USER_STATE + 40; // skip directly to the ')'
            } break;

            // if the expression is present then the 'as' keyword is optional
            case USER_STATE + 10: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_AS) {
                    consume_token();
                    state = USER_STATE + 20;
                }
                else
                    state = USER_STATE + 40; // skip to the ')'
            } break;

            // if the 'as' keyword is present, then the type specifier is optional
            case USER_STATE + 20: {
                TRACE_STATE;
                type_specifier = _parse_type_specifier(context);
                state = USER_STATE + 30;
            } break;

            // if the 'as' keyword is present then the identifier is required
            case USER_STATE + 30: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = USER_STATE + 40;
                else {
                    parser_expect_error(context, "an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            // if the left paren is present, then the right paren is required
            case USER_STATE + 40: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = USER_STATE + 100;
                }
                else {
                    parser_expect_error(context, "a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            // loop body is not optional
            case USER_STATE + 100: {
                TRACE_STATE;
                if(NULL != (loop_body = _parse_loop_body(context)))
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a loop body");
                    state = USER_STATE + 100;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_for_clause_t*)create_ast_node(AST_FOR_CLAUSE);
                node->identifier = identifier;
                node->expr = expr;
                node->type_specifier = type_specifier;
                node->loop_body = loop_body;
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
