
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_definition
 *      : type_specifier IDENTIFIER '.' IDENTIFIER function_definition_parameters function_body
 *      ;
 */
void _traverse_function_definition(ast_function_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);
    _traverse_identifier(node->group);
    _traverse_identifier(node->name);
    _traverse_function_definition_parameters(node->function_definition_parameters);
    _traverse_function_body(node->function_body);

    RETURN();
}
