
/*
 * this is a generated file
 */
#include "ast.h"
#include "common.h"
#include "parser.h"
#include "token_queue.h"

// for open_file();
#include "fileio.h"

/*
 *  This parser function can only return a namespace item. The include and
 *  import non-terminals are handled in this function. They are placed into
 *  the AST tree, but no functionality is attached to them by default.
 *
 *  module_item
 *      : namespace_item
 *      | include_statement
 *      | import_statement
 *      ;
 *
 *  typedef struct _ast_module_item_t {
 *      ast_node_t node;
 *      ast_node_t* item;
 *  } ast_module_item_t;
 *
 *   typedef struct _ast_include_statement_t {
 *      ast_node_t node;
 *      // include is handled outside of the AST
 *      struct _ast_string_literal_t* str;
 *  } ast_include_statement_t;
 *
 *  typedef struct _ast_import_statement_t {
 *      ast_node_t node;
 *      // import is handled outside of the AST
 *      struct _ast_compound_name_t* compound_name;
 *      struct _ast_string_literal_t* str;
 *      struct _ast_identifier_t* identifier;
 *  } ast_import_statement_t;
 */
ast_module_item_t* _parse_module_item(parser_context_t* context) {

    ENTER;
    ast_module_item_t* node = NULL;
    ast_node_t* item = NULL;

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_namespace_item(context)))
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 1;
            } break;

            case START_STATE + 1: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_include_statement(context))) 
                    state = RETURN_MATCH;
                else
                    state = START_STATE + 2;
            } break;

            case START_STATE + 2: {
                TRACE_STATE;
                if(NULL != (item = (ast_node_t*)_parse_import_statement(context))) {
                    string_t* str = ((ast_include_statement_t*)item)->str->str;
                    open_file(find_file(str));
                    push_parser_mode(context, PMODE_IMPORT);
                    state = RETURN_MATCH;
                }
                else
                    state = RETURN_NO_MATCH;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = (ast_module_item_t*)create_ast_node(AST_MODULE_ITEM);
                node->item = item;
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
