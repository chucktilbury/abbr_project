
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  exit_statement
 *      : 'exit' '(' expression? ')'
 *      ;
 */
void _traverse_exit_statement(ast_exit_statement_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL)
        _traverse_expression(node->expr);

    RETURN();
}
