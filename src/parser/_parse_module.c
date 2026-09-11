
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

// for close_file()
#include "fileio.h"

/*
 *  This parser routine is different from the others because it is the
 *  only place a EOF is acceptable. It also has to make sure that only
 *  one start clause has been seen.
 *
 *  module
 *      : module_item*
 *      | start clause
 *      ;
 *
 *  typedef struct _ast_module_t {
 *      ast_node_t node;
 *      ast_node_list_t* list;
 *  } ast_module_t;
 */
ast_module_t* _parse_module(parser_context_t* context) {

    ENTER;
    ast_module_t* node = NULL;
    ast_node_list_t* list = NULL;
    ast_node_t* item = NULL;
    bool start_clause = false;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            // needs to check for end of file at every iteration
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_END_OF_FILE) {
                    consume_token();
                    pop_parser_mode(context);
                    close_file();
                    state = START_STATE+1;
                }
                else if(list == NULL)
                    state = START_STATE+2;
                else
                    state = START_STATE+4;
            } break;

            // If end of file was seen, then check for end of input. If not
            // then continue with the main line of parsing.
            case START_STATE+1: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_END_OF_INPUT) {
                    consume_token();
                    pop_parser_mode(context);
                    state = RETURN_MATCH;
                }
                else if(list == NULL)
                    state = START_STATE+2;
                else
                    state = START_STATE+4;
            } break;

            // if the list has not already been created, then create it and
            // add the item
            case START_STATE+2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_start_clause(context))) {
                    if(!start_clause) {
                        list = create_ast_node_list();
                        append_ast_node_list(list, item);
                        state = START_STATE;
                        start_clause = true;
                    }
                    else {
                        parser_error(context, "only one start clause is allowed");
                        state = RETURN_ERROR;
                    }
                }
                else
                    state = START_STATE+3;
            } break;

            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_module_item(context))) {
                    list = create_ast_node_list();
                    append_ast_node_list(list, item);
                    state = START_STATE;
                }
                else {
                    parser_error(context, "expected end of file or module item");
                    state = RETURN_ERROR;
                }
            } break;

            // if the list has already been created, then just add to it
            case START_STATE+4: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_start_clause(context))) {
                    if(!start_clause) {
                        append_ast_node_list(list, item);
                        state = START_STATE;
                        start_clause = true;
                    }
                    else {
                        parser_error(context, "only one start clause is allowed");
                        state = RETURN_ERROR;
                    }
                }
                else
                    state = START_STATE+5;
            } break;

            case START_STATE+5: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_module_item(context))) {
                    append_ast_node_list(list, item);
                    state = START_STATE;
                }
                else {
                    parser_error(context, "expected end of file or module item");
                    state = RETURN_ERROR;
                }
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_module_t*)create_ast_node(AST_MODULE);
                node->list = list;
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

