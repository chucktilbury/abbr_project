
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  include_statement
 *      : 'include' string_literal
 *      ;
 */
void _traverse_include_statement(ast_include_statement_t* node) {
    TRAVERSE_ENTER;

    // includes are handled during parsing. this should probably never be called.
    _traverse_string_literal(node->str);
    RETURN();
}

