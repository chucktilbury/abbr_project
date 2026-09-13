
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  array_parameters
 *      : '[' (array_parameters | expression) ']'
 *      ;
 */
void _traverse_array_parameters(ast_array_parameters_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_ARRAY_PARAMETERS:
            _traverse_array_parameters((ast_array_parameters_t*)node->item);
            break;
        case AST_EXPRESSION:
            _traverse_expression((ast_expression_t*)node->item);
            break;
        default:
            FATAL("invalid node type");
    }

    RETURN();
}
