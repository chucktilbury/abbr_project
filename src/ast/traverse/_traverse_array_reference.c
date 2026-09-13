
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  array_reference
 *      : IDENTIFIER array_parameters (array_parameters)*
 *      ;
 */
void _traverse_array_reference(ast_array_reference_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->array_parameters, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->array_parameters, &mark)) {
        _traverse_array_parameters((ast_array_parameters_t*)ptr);
    }

    RETURN();
}
