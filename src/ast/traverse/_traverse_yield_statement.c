
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 */
void _traverse_yield_statement(ast_yield_statement_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);

    RETURN();
}
