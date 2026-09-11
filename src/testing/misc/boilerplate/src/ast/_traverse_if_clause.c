
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 */
void _traverse_if_clause(ast_if_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);
    _traverse_function_body(node->function_body);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->else_clause, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->else_clause, &mark)) {
        _traverse_else_clause((ast_else_clause_t*)ptr);
    }

    if(node->final_else_clause != NULL) {
        _traverse_final_else_clause(node->final_else_clause);
    }

    RETURN();
}

