
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  destructor_declaration
 *      : 'destroy' function_body?
 *      ;
 */
void _traverse_destructor_declaration(ast_destructor_declaration_t* node) {
    TRAVERSE_ENTER;

    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}

