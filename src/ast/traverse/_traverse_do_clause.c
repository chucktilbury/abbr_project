
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 */
void _traverse_do_clause(ast_do_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}
