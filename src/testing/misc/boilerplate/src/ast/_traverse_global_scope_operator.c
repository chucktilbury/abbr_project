
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  global_scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 */
void _traverse_global_scope_operator(ast_global_scope_operator_t* node) {
    TRAVERSE_ENTER;

    SHOW_TOKEN_TYPE(node->tok);

    RETURN();
}

