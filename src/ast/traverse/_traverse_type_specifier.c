
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  type_specifier
 *      : literal_type
 *      | compound_name
 *      ;
 */
void _traverse_type_specifier(ast_type_specifier_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_COMPOUND_NAME:
            _traverse_compound_name((ast_compound_name_t*)node->item);
            break;
        case AST_LITERAL_TYPE:
            _traverse_literal_type((ast_literal_type_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

