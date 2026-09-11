
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  try_clause
 *      : 'try' function_body ( except_clause )+ finally_clause?
 *      ;
 *
 *  typedef struct _ast_try_clause_t {
 *      ast_node_t node;
 *      struct _ast_function_body_t* function_body;
 *      struct _ast_finally_clause_t* finally_clause;
 *      ast_node_list_t* except_clause;
 *  } ast_try_clause_t;
 */
ast_try_clause_t* _parse_try_clause(parser_context_t* context) {

    ENTER;
    ast_try_clause_t* node = NULL;
    ast_function_body_t* function_body = NULL;
    ast_finally_clause_t* finally_clause = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_TRY) {
                    consume_token();
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required function body
            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (function_body = _parse_function_body(context))) {
                    state = START_STATE+2;
                }
                else {
                    parser_error(context, "expected a function body");
                    state = RETURN_ERROR;
                }
            } break;

            // required first except clause
            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_except_clause(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE+3;
                }
                else {
                    parser_error(context, "expected a function body");
                    state = RETURN_ERROR;
                }
            } break;

            // optional except clause
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_except_clause(context)))
                    append_ast_node_list(list, item);
                else
                    state = START_STATE+4;
            } break;

            // optional finally clause
            case START_STATE+4: {
                TRACE_STATE;
                finally_clause = _parse_finally_clause(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_try_clause_t*)create_ast_node(AST_TRY_CLAUSE);
                node->function_body = function_body;
                node->finally_clause = finally_clause;
                node->except_clause = list;
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

