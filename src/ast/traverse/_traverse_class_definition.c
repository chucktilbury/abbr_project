
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  class_definition
 *      : 'class' IDENTIFIER ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
 *      ;
 */
void _traverse_class_definition(ast_class_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->i_list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->i_list, &mark)) {
        _traverse_inheritance_item((ast_inheritance_item_t*)ptr);
    }

    mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->c_list, &mark);
        ptr != NULL; ptr = iterate_ast_node_list(node->c_list, &mark)) {
        _traverse_class_item((ast_class_item_t*)ptr);
    }

    RETURN();
}
