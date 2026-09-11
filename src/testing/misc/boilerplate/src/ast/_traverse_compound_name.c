
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  compound_name
 *      : IDENTIFIER ('.' IDENTIFIER)*
 *      ;
 */
void _traverse_compound_name(ast_compound_name_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_identifier((ast_identifier_t*)ptr);
    }

    RETURN();
}

