
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 *
 *  typedef struct _ast_raise_statement_t {
 *      ast_node_t node;
 *      struct _ast_compound_name_t* compound_name;
 *  } ast_raise_statement_t;
 */
ast_raise_statement_t* _parse_raise_statement(parser_context_t* context) {

    ENTER;
    ast_raise_statement_t* node = NULL;
    ast_compound_name_t* compound_name = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RAISE) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required '('
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 2;
                }
                else {
                    parser_expect_error(context, "a '('");
                    state = RETURN_ERROR;
                }
            } break;

            // required compound name
            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (compound_name = _parse_compound_name(context))) {
                    state = START_STATE + 3;
                }
                else {
                    parser_expect_error(context, "a class name");
                    state = RETURN_ERROR;
                }
            } break;

            // required ')'
            case START_STATE + 3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) {
                    consume_token();
                    state = RETURN_MATCH;
                }
                else {
                    parser_expect_error(context, "a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_raise_statement_t*)create_ast_node(AST_RAISE_STATEMENT);
                node->compound_name = compound_name;
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
