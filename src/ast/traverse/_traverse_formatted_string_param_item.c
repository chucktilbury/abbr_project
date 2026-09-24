
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  formatted_string_param_item
 *      : expression
 *      | IDENTIFIER '=' expression
 *      ;
 */
void _traverse_formatted_string_param_item(ast_formatted_string_param_item_t* node) {
    TRAVERSE_ENTER;

    if(node->identifier != NULL)
        _traverse_identifier(node->identifier);
    _traverse_expression(node->expr);

    RETURN();
}
