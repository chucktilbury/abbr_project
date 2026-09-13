
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 */
void _traverse_compound_reference(ast_compound_reference_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_compound_reference_item((ast_compound_reference_item_t*)ptr);
    }

    RETURN();
}
