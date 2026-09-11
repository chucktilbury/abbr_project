
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_array_definition
 *      : '[' const_value (',' const_value)* ']'
 *      ;
 */
void _traverse_literal_array_definition(ast_literal_array_definition_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->const_value, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->const_value, &mark)) {
        _traverse_const_value((ast_const_value_t*)ptr);
    }

    RETURN();
}

