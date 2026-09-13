
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 */
void _traverse_final_else_clause(ast_final_else_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}
