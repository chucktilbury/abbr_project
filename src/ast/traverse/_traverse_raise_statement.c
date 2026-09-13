
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 */
void _traverse_raise_statement(ast_raise_statement_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_name(node->compound_name);

    RETURN();
}
