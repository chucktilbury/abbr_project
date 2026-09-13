
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' identifier)? ')' function_body
 *      ;
 *
 *  typedef struct _ast_except_clause_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      struct _ast_compound_name_t* compound_name;
 *      struct _ast_function_body_t* function_body;
 *  } ast_except_clause_t;
 */
ast_except_clause_t* _parse_except_clause(parser_context_t* context) {

    ENTER;
    ast_except_clause_t* node = NULL;
    ast_identifier_t* identifier = NULL;
    ast_compound_name_t* compound_name = NULL;
    ast_function_body_t* function_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_EXCEPT) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // parens are required
            case START_STATE + 2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LPAREN) {
                    consume_token();
                    state = START_STATE + 3;
                }
                else {
                    parser_error(context, "expected a '('");
                    state = RETURN_ERROR;
                }
            } break;

            // compound name is required
            case START_STATE + 3: {
                TRACE_STATE;
                if(NULL != (compound_name = _parse_compound_name(context)))
                    state = START_STATE + 4;
                else {
                    parser_error(context, "expected a compound identifier");
                    state = RETURN_ERROR;
                }
            } break;

            // the 'as' token is optional
            case START_STATE + 4: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_AS) {
                    consume_token();
                    // require the identifier
                    state = START_STATE + 5;
                }
                else // require the ')'
                    state = START_STATE + 6;
            } break;

            // required identifier
            case START_STATE + 5: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = START_STATE + 6;
                else {
                    parser_error(context, "expected an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            case START_STATE + 6: {
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
                node = (ast_except_clause_t*)create_ast_node(AST_EXCEPT_CLAUSE);
                node->identifier = identifier;
                node->compound_name = compound_name;
                node->function_body = function_body;
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
