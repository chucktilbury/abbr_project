
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_body
 *      : '{' function_body_item+ '}'
 *      ;
 */
void _traverse_function_body(ast_function_body_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_function_body_item((ast_function_body_item_t*)ptr);
    }

    RETURN();
}

