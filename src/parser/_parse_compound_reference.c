
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 *
 *  typedef struct _ast_compound_reference_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_compound_reference_t;
 */
ast_compound_reference_t* _parse_compound_reference(parser_context_t* context) {

    ENTER;
    ast_compound_reference_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_compound_reference_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // if there is a '.' after the item, then loop, otherwise match
            case START_STATE + 1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_DOT) {
                    consume_token();
                    state = REPEAT_STATE;
                }
                else
                    state = RETURN_MATCH;
            } break;

            case REPEAT_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_compound_reference_item(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE + 1;
                }
                else {
                    parser_error(context, "expected an identifier, an array reference, or a function_reference");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_compound_reference_t*)create_ast_node(AST_COMPOUND_REFERENCE);
                // ast elements here
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
