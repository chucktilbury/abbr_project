
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
ast_while_clause_t* _parse_while_clause(parser_context_t* context) {

    ENTER;
    ast_while_clause_t* node = NULL;
    // ast elements here

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_while_clause_t*)create_ast_node(AST_WHILE_CLAUSE);
                // ast elements here
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

