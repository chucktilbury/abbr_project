
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  formatted_string_param_list
 *      : '(' ( formatted_string_param_item, (',' formatted_string_param_item)* )? ')'
 *      ;
 */
void _traverse_formatted_string_param_list(ast_formatted_string_param_list_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_formatted_string_param_item((ast_formatted_string_param_item_t*)ptr);
    }

    RETURN();
}
