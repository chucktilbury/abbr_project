
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  data_declaration
 *      : type_specifier IDENTIFIER ( '=' const_value )?
 *      ;
 */
void _traverse_data_declaration(ast_data_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);
    _traverse_identifier(node->identifier);

    if(node->const_value != NULL)
        _traverse_const_value(node->const_value);

    RETURN();
}
