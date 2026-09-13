
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  try_clause
 *      : 'try' function_body except_clause+ finally_clause?
 *      ;
 */
void _traverse_try_clause(ast_try_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->except_clause, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->except_clause, &mark)) {
        _traverse_except_clause((ast_except_clause_t*)ptr);
    }

    if(node->finally_clause != NULL)
        _traverse_finally_clause(node->finally_clause);

    RETURN();
}
