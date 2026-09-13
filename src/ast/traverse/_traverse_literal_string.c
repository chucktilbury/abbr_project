
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 */
void _traverse_literal_string(ast_literal_string_t* node) {
    TRAVERSE_ENTER;

    if(node->literal_str != NULL) {
        SHOW_STRING(node->literal_str);
    }
    else
        _traverse_formatted_string(node->formatted_string);

    RETURN();
}
