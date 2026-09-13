
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_dict_item
 *      : string_literal ':' const_value
 *      ;
 */
void _traverse_literal_dict_item(ast_literal_dict_item_t* node) {
    TRAVERSE_ENTER;

    _traverse_string_literal(node->literal_str);
    _traverse_const_value(node->const_value);

    RETURN();
}
