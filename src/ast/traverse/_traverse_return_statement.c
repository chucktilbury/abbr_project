
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  return_statement
 *      : 'return' ( '(' expression? ')' )?
 *      ;
 */
void _traverse_return_statement(ast_return_statement_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL)
        _traverse_expression(node->expr);

    RETURN();
}
