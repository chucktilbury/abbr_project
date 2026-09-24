
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  class_body
 *      : '{' class_item+ '}'
 *      ;
 */
void _traverse_class_body(ast_class_body_t* node) {
    TRAVERSE_ENTER;
    
    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_class_item((ast_class_item_t*)ptr);
    }

    RETURN();
}
