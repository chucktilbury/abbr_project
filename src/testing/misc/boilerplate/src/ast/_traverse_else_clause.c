
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 */
void _traverse_else_clause(ast_else_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);
    _traverse_function_body(node->function_body);

    RETURN();
}

