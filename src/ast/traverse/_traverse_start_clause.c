
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  start_clause
 *      : 'start' function_body
 *      ;
 */
void _traverse_start_clause(ast_start_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}
