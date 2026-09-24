
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  inheritance_list
 *      : '(' (inheritance_item (',' inheritance_item)*)? ')'
 *      ;
 */
void _traverse_inheritance_list(ast_inheritance_list_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_inheritance_item((ast_inheritance_item_t*)ptr);
    }

    RETURN();
}
