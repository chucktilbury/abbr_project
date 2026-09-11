
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  constructor_definition
 *      : IDENTIFIER '.' 'create' function_definition_parameters function_body
 *      ;
 */
void _traverse_constructor_definition(ast_constructor_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->group);
    _traverse_function_definition_parameters(node->function_definition_parameters);
    _traverse_function_body(node->function_body);

    RETURN();
}

