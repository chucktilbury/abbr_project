
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  import_statement
 *      : 'import' string_literal
 *      | 'import' compound_name ( ('from' string_literal)? ('as' identifier)? )?
 *      ;
 */
ast_import_statement_t* _parse_import_statement(parser_context_t* context) {

    ENTER;
    ast_import_statement_t* node = NULL;
    // ast elements here

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_import_statement_t*)create_ast_node(AST_IMPORT_STATEMENT);
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

