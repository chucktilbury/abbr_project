
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
void _traverse_formatted_string(ast_formatted_string_t* node) {
    TRAVERSE_ENTER;

    SHOW_STRING(node->literal_str);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_expression((ast_expression_t*)ptr);
    }

    RETURN();
}
