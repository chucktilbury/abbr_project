
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "fileio.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  include_statement
 *      : 'include' string_literal
 *      ;
 *
 *  typedef struct _ast_include_statement_t {
 *      ast_node_t node;
 *      // include is handled outside of the AST
 *      struct _ast_string_literal_t* str;
 *  } ast_include_statement_t;
 */
ast_include_statement_t* _parse_include_statement(parser_context_t* context) {

    ENTER;
    ast_include_statement_t* node = NULL;
    ast_string_literal_t* str_lit;
    string_t* str;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_INCLUDE) {
                    consume_token();
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // need to parse string_literal directly to avoid flushing the token queue.
            case START_STATE+1: {
                TRACE_STATE;
                TRACE_TOKEN;
                if(TOKEN_TYPE == TOK_LITERAL_SSTR || TOKEN_TYPE == TOK_LITERAL_DSTR) {
                    str = copy_string(get_token()->text);
                    str_lit = (ast_string_literal_t*)create_ast_node(AST_STRING_LITERAL);
                    str_lit->str = str;
                    state = RETURN_MATCH;
                }
                else {
                    parser_error(context, "expected a literal string");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_include_statement_t*)create_ast_node(AST_INCLUDE_STATEMENT);
                node->str = str_lit;
                
                flush_token_queue();

                TRACE("file name: %s", raw_string(str));
                open_file(find_file(str));
                push_parser_mode(context, PMODE_INCLUDE);
                consume_token();
                
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
