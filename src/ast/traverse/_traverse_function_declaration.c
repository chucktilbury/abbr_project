
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_declaration
 *      : type_specifier IDENTIFIER function_declaration_parameters function_body?
 *      ;
 */
void _traverse_function_declaration(ast_function_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);
    _traverse_type_specifier(node->type_specifier);
    _traverse_function_declaration_parameters(node->function_declaration_parameters);

    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}
