
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  type_cast
 *      : '(' type_specifier ')' expression
 *      ;
 */
void _traverse_type_cast(ast_type_cast_t* node) {
    TRAVERSE_ENTER;
    
    _traverse_type_specifier(node->type);
    _traverse_expression(node->expr);
    
    RETURN();
}
