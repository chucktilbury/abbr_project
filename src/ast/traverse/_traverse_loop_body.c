
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  loop_body
 *      : '{' loop_body_item* '}'
 *      ;
 */
void _traverse_loop_body(ast_loop_body_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_loop_body_item((ast_loop_body_item_t*)ptr);
    }

    RETURN();
}
