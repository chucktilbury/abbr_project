
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters function_body?
 *      ;
 */
void _traverse_constructor_declaration(ast_constructor_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_declaration_parameters(node->function_declaration_parameters);
    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}

