
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  finally_clause
 *      : 'finally' function_body
 *      ;
 */
void _traverse_finally_clause(ast_finally_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}

