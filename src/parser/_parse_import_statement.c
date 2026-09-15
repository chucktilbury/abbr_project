
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "fileio.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  import_statement
 *      : 'import' string_literal ('as' identifier)?
 *      ;
 *  
 *  typedef struct _ast_import_statement_t {
 *      ast_node_t node;
 *      // import is handled outside of the AST
 *      struct _ast_string_literal_t* str;
 *      struct _ast_identifier_t* identifier;
 *  } ast_import_statement_t;
 */
ast_import_statement_t* _parse_import_statement(parser_context_t* context) {

    ENTER;
    ast_import_statement_t* node = NULL;
    ast_string_literal_t* str = NULL;
    ast_identifier_t* identifier = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_IMPORT) {
                    consume_token();
                    state = START_STATE+1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required literal string
            case START_STATE+1: {
                TRACE_STATE;
                if(NULL != (str = _parse_string_literal(context)))
                    state = START_STATE+2;
                else {
                    parser_error(context, "expected a literal string");
                    state = RETURN_ERROR;
                }
            } break;

            // optional 'as' keyword
            case START_STATE+2: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_AS){
                    consume_token();
                    state = START_STATE+3;
                }
                else
                    state = RETURN_MATCH;
            } break;

            // if 'as' was seen then an identifier is required
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (identifier = _parse_identifier(context)))
                    state = RETURN_MATCH;
                else {
                    parser_error(context, "expected an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_import_statement_t*)create_ast_node(AST_IMPORT_STATEMENT);
                node->str = str;
                node->identifier = identifier;

                open_file(find_file(str->str));
                push_parser_mode(context, PMODE_IMPORT);
            TRACE_TOKEN;
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
