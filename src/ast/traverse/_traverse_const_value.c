
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  const_value
 *      : literal_number
 *      | string_literal
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 */
void _traverse_const_value(ast_const_value_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_LITERAL_ARRAY_DEFINITION:
            _traverse_literal_array_definition(((ast_literal_array_definition_t*)node->item));
            break;
        case AST_LITERAL_DICT_DEFINITION:
            _traverse_literal_dict_definition(((ast_literal_dict_definition_t*)node->item));
            break;
        case AST_LITERAL_NUMBER:
            _traverse_literal_number(((ast_literal_number_t*)node->item));
            break;
        case AST_STRING_LITERAL:
            _traverse_string_literal(((ast_string_literal_t*)node->item));
            break;
        default:
            FATAL("invalid node type");
    }

    RETURN();
}
