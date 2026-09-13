
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  compound_reference_item
 *      : IDENTIFIER
 *      | function_reference
 *      | array_reference
 *      ;
 */
void _traverse_compound_reference_item(ast_compound_reference_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_FUNCTION_REFERENCE:
            _traverse_function_reference((ast_function_reference_t*)node->item);
            break;
        case AST_ARRAY_REFERENCE:
            _traverse_array_reference((ast_array_reference_t*)node->item);
            break;
        case AST_IDENTIFIER:
            _traverse_identifier((ast_identifier_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}
