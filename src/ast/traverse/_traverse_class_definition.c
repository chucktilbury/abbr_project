
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  class_definition
 *      : 'class' IDENTIFIER inheritance_list? class_body
 *      ;
 */
void _traverse_class_definition(ast_class_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);
    _traverse_inheritance_list((ast_inheritance_list_t*)node->i_list);
    _traverse_class_body((ast_class_body_t*)node->c_list);

    RETURN();
}
