
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
 *  string_literal
 *      : LITERAL_SSTR
 *      | LITERAL_DSTR
 *      ;
 *
 *  typedef struct _ast_string_literal_t {
 *      ast_node_t node;
 *      string_t* str;
 *  } ast_string_literal_t;
 */
ast_string_literal_t* _parse_string_literal(parser_context_t* context) {

    ENTER;
    ast_string_literal_t* node = NULL;
    string_t* str = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_LITERAL_SSTR || TOKEN_TYPE == TOK_LITERAL_SSTR) {
                    consume_token();
                    str = copy_string(get_token()->text);
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_string_literal_t*)create_ast_node(AST_STRING_LITERAL);
                node->str = str;
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

