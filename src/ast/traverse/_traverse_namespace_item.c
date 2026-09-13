
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  namespace_item
 *      : global_scope_operator
 *      | class_definition
 *      | function_definition
 *      | constructor_definition
 *      | destructor_definition
 *      | namespace
 *      ;
 */
void _traverse_namespace_item(ast_namespace_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_GLOBAL_SCOPE_OPERATOR:
            _traverse_global_scope_operator((ast_global_scope_operator_t*)node->item);
            break;
        case AST_CLASS_DEFINITION:
            _traverse_class_definition((ast_class_definition_t*)node->item);
            break;
        case AST_FUNCTION_DEFINITION:
            _traverse_function_definition((ast_function_definition_t*)node->item);
            break;
        case AST_CONSTRUCTOR_DEFINITION:
            _traverse_constructor_definition((ast_constructor_definition_t*)node->item);
            break;
        case AST_DESTRUCTOR_DEFINITION:
            _traverse_destructor_definition((ast_destructor_definition_t*)node->item);
            break;
        case AST_NAMESPACE:
            _traverse_namespace((ast_namespace_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}
