
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  module
 *      : module_item*
 *      | start_clause
 *      ;
 */
void _traverse_module(ast_module_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL;
                ptr = iterate_ast_node_list(node->list, &mark)) {

        switch(NODE_TYPE(ptr)) {
            case AST_MODULE_ITEM:
                _traverse_module_item((ast_module_item_t*)ptr);
                break;
            case AST_START_CLAUSE:
                _traverse_start_clause((ast_start_clause_t*)ptr);
                break;
            default:
                FATAL("unknown node type");
        }
    }
    RETURN();
}

