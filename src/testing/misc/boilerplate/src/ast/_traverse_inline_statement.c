
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 * Note that this is returned by the scanner as a TOK_INLINE token.
 *
 *  inline_statement
 *      : 'inline' '{' RAW_TEXT '}'
 */
void _traverse_inline_statement(ast_inline_statement_t* node) {
    TRAVERSE_ENTER;

    SHOW_STRING(node->str);

    RETURN();
}

