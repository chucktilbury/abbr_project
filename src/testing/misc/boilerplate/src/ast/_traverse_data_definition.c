
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  data_definition
 *      : type_specifier IDENTIFIER ( '=' expression )?
 *      ;
 */
void _traverse_data_definition(ast_data_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);
    _traverse_type_specifier(node->type_specifier);
    if(node->expression != NULL)
        _traverse_expression(node->expression);

    RETURN();
}

