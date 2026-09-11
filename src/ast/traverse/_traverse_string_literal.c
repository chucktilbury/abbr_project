
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  string_literal
 *      : LITERAL_DSTR
 *      | LITERAL_SSTR
 *      ;
 */
void _traverse_string_literal(ast_string_literal_t* node) {
    TRAVERSE_ENTER;
    SHOW_STRING(node->str);
    RETURN();
}

