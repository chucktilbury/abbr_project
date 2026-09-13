
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  class_scope_operator
 *      : 'public'
 *      | 'private'
 *      | 'protected'
 *      ;
 */
void _traverse_class_scope_operator(ast_class_scope_operator_t* node) {
    TRAVERSE_ENTER;

    SHOW_TOKEN_TYPE(node->tok);

    RETURN();
}
