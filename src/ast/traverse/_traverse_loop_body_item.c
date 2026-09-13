
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | break_statement
 *      | continue_statement
 *      | loop_body
 *      ;
 */
void _traverse_loop_body_item(ast_loop_body_item_t* node) {
    TRAVERSE_ENTER;

    if(node->item != NULL) {
        switch(NODE_TYPE(node->item)) {
            case AST_FUNCTION_BODY_ITEM:
                _traverse_function_body_item((ast_function_body_item_t*)node->item);
                break;
            case AST_YIELD_STATEMENT:
                _traverse_yield_statement((ast_yield_statement_t*)node->item);
                break;
            case AST_BREAK_STATEMENT:
                _traverse_break_statement((ast_break_statement_t*)node->item);
                break;
            case AST_CONTINUE_STATEMENT:
                _traverse_continue_statement((ast_continue_statement_t*)node->item);
                break;
            case AST_LOOP_BODY:
                _traverse_loop_body((ast_loop_body_t*)node->item);
                break;
            default:
                FATAL("invalid node type");
        }
    }

    RETURN();
}
