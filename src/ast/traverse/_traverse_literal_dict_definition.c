
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_dict_definition
 *      : '[' literal_dict_item (',' literal_dict_item)* ']'
 *      ;
 */
void _traverse_literal_dict_definition(ast_literal_dict_definition_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->literal_dict_item, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->literal_dict_item, &mark)) {
        _traverse_literal_dict_item((ast_literal_dict_item_t*)ptr);
    }

    RETURN();
}
