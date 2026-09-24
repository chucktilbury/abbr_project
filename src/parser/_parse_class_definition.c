
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

/*
 *  class_definition
 *      : 'class' identifier inheritance_list? class_body
 *      ;
 *
 *  typedef struct _ast_class_definition_t {
 *      ast_node_t node;
 *      struct _ast_identifier_t* identifier;
 *      ast_inheritance_list_t* i_list;
 *      ast_class_body_t* c_list;
 *  } ast_class_definition_t;
 */
ast_class_definition_t* _parse_class_definition(parser_context_t* context) {

    ENTER;
    ast_class_definition_t* node = NULL;
    ast_identifier_t* ident = NULL;
    ast_inheritance_list_t* ilist = NULL;
    ast_class_body_t* clist = NULL;
    symbol_t* symbol = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(TOKEN_TYPE == TOK_CLASS) {
                    consume_token();
                    state = START_STATE + 1;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            // required identifier
            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (ident = _parse_identifier(context)))
                    state = USER_STATE;
                else {
                    parser_expect_error(context, "an identifier");
                    state = RETURN_ERROR;
                }
            } break;

            // optional inheritance list
            case START_STATE+2: {
                TRACE_STATE;
                ilist = _parse_inheritance_list(context);
                state = START_STATE+3;
            } break;

            // required class body
            case START_STATE+3: {
                TRACE_STATE;
                if(NULL != (clist = _parse_class_body(context))) 
                    state = RETURN_MATCH;
                else {
                    parser_expect_error(context, "a class body");
                    state = RETURN_ERROR;
                }
            } break;


            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_class_definition_t*)create_ast_node(AST_CLASS_DEFINITION);
                node->identifier = ident;
                node->i_list = ilist;
                node->c_list = clist;
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

