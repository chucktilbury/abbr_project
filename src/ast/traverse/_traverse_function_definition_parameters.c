
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 */
void _traverse_function_definition_parameters(ast_function_definition_parameters_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->data_declaration, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->data_declaration, &mark)) {
        _traverse_data_declaration((ast_data_declaration_t*)ptr);
    }

    RETURN();
}
