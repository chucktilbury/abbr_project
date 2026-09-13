
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  primary_expression
 *      : literal_number
 *      | literal_string
 *      | compound_reference
 *      ;
 */
void _traverse_primary_expression(ast_primary_expression_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->value)) {
        case AST_LITERAL_STRING:
            _traverse_literal_string((ast_literal_string_t*)node->value);
            break;
        case AST_LITERAL_NUMBER:
            _traverse_literal_number((ast_literal_number_t*)node->value);
            break;
        case AST_COMPOUND_REFERENCE:
            _traverse_compound_reference((ast_compound_reference_t*)node->value);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}
