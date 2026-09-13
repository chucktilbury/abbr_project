
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_number
 *      : LITERAL_INT
 *      | LITERAL_UINT
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      ;
 */
void _traverse_literal_number(ast_literal_number_t* node) {
    TRAVERSE_ENTER;
    SHOW_TOKEN_TYPE(node->value_type);
    // not showing the union with the actual values. This is set by the parser.
    RETURN();
}
