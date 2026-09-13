
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  class_item
 *      : class_scope_operator
 *      | function_declaration
 *      | data_declaration
 *      | constructor_declaration
 *      | destructor_declaration
 *      ;
 */
void _traverse_class_item(ast_class_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_CLASS_SCOPE_OPERATOR:
            _traverse_class_scope_operator((ast_class_scope_operator_t*)node->item);
            break;
        case AST_FUNCTION_DECLARATION:
            _traverse_function_declaration((ast_function_declaration_t*)node->item);
            break;
        case AST_DATA_DECLARATION:
            _traverse_data_declaration((ast_data_declaration_t*)node->item);
            break;
        case AST_CONSTRUCTOR_DECLARATION:
            _traverse_constructor_declaration((ast_constructor_declaration_t*)node->item);
            break;
        case AST_DESTRUCTOR_DECLARATION:
            _traverse_destructor_declaration((ast_destructor_declaration_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}
