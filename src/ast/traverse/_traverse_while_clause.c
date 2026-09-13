
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
void _traverse_while_clause(ast_while_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}
