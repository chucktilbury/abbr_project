
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  namespace
 *      : 'namespace' IDENTIFIER '{' namespace_item* '}'
 *      ;
 */
void _traverse_namespace(ast_namespace_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_namespace_item((ast_namespace_item_t*)ptr);
    }

    RETURN();
}
