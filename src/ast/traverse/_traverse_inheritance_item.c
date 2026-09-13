
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 */
void _traverse_inheritance_item(ast_inheritance_item_t* node) {
    TRAVERSE_ENTER;

    if(node->class_scope_operator != NULL)
        _traverse_class_scope_operator(node->class_scope_operator);

    _traverse_compound_name(node->compound_name);

    RETURN();
}
