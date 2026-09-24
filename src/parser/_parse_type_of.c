
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  type_of
 *      : 'type' '(' expression ')' 
 *      ;
 *
 *  typedef struct _ast_type_of_t {
 *      ast_node_t node;
 *      struct _ast_expression_t* expr;
 *  } ast_type_of_t;
 */
ast_type_of_t* _parse_type_of(parser_context_t* context) {

    ENTER;
    ast_type_of_t* node = NULL;
    ast_expression_t* expr = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_TYPE) 
                    state = START_STATE+1;
                else    
                    state = RETURN_NO_MATCH;
            } break;

            case START_STATE+1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) 
                    state = START_STATE+2;
                else {   
                    parser_expect_error(context, "a '('");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (expr = _parse_expression(context)))
                    state = START_STATE + 3;
                else {
                    parser_expect_error(context, "an expression");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE+3: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_RPAREN) 
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a ')'");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_type_of_t*)create_ast_node(AST_TYPE_OF);
                node->expr = expr;
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
