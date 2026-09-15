
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  import_statement
 *      : 'import' string_literal ('as' IDENTIFIER)?
 *      ;
 */
void _traverse_import_statement(ast_import_statement_t* node) {
    TRAVERSE_ENTER;

    // imports are handled during parsing. this should probably never be called.
    _traverse_string_literal(node->str);
    if(node->identifier != NULL)
        _traverse_identifier(node->identifier);
    RETURN();
}
