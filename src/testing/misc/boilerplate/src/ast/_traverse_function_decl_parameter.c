
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  function_decl_parameter
 *      : type_specifier (IDENTIFIER)?
 *      ;
 */
void _traverse_function_decl_parameter(ast_function_decl_parameter_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);

    _traverse_identifier(node->identifier);

    RETURN();
}

