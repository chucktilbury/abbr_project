
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  type_of
 *      : 'type' '(' expression ')' 
 *      ;
 */
void _traverse_type_of(ast_type_of_t* node) {
    TRAVERSE_ENTER;
    
    _traverse_expression(node->expr);
    
    RETURN();
}
