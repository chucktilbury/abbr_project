
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_reference
 *      : IDENTIFIER '(' expression (',' expression)* ')'
 *      ;
 */
void _traverse_function_reference(ast_function_reference_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->expr, &mark);
            ptr != NULL; ptr = iterate_ast_node_list(node->expr, &mark)) {
        _traverse_expression((ast_expression_t*)ptr);
    }

    RETURN();
}

