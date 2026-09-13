
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 */
void _traverse_function_declaration_parameters(ast_function_declaration_parameters_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_function_decl_parameter((ast_function_decl_parameter_t*)ptr);
    }
    RETURN();
}
