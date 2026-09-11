
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  destructor_definition
 *      : IDENTIFIER '.' 'destroy' function_body
 *      ;
 */
void _traverse_destructor_definition(ast_destructor_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->group);
    _traverse_function_body(node->function_body);

    RETURN();
}

