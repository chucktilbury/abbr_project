
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  module_item
 *      : namespace_item
 *      | include_statement
 *      | import_statement
 *      ;
 */
void _traverse_module_item(ast_module_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_NAMESPACE_ITEM:
            _traverse_namespace_item((ast_namespace_item_t*)node->item);
            break;
        // There is no reason to traverse includes or imports. That is handled
        // completely by the parser.
        case AST_INCLUDE_STATEMENT:
            _traverse_include_statement((ast_include_statement_t*)node->item);
            break;
        case AST_IMPORT_STATEMENT:
            _traverse_import_statement((ast_import_statement_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

