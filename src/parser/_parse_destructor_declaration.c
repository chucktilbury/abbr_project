
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  destructor_declaration
 *      : 'destroy' function_body?
 *      ;
 *
 *  typedef struct _ast_destructor_declaration_t {
 *      ast_node_t node;
 *      struct _ast_function_body_t* func_body;
 *  } ast_destructor_declaration_t;
 */
ast_destructor_declaration_t* _parse_destructor_declaration(parser_context_t* context) {

    ENTER;
    ast_destructor_declaration_t* node = NULL;
    ast_function_body_t* func_body = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DESTROY) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // function body is optional
            case START_STATE + 1: {
                TRACE_STATE;
                func_body = _parse_function_body(context);
                state = RETURN_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_destructor_declaration_t*)create_ast_node(AST_DESTRUCTOR_DECLARATION);
                node->func_body = func_body;
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
