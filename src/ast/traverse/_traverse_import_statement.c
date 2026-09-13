
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  import_statement
 *      : 'import' (LITERAL_DSTR | LITERAL_SSTR)
 *      | 'import' compound_name ( ('from' (LITERAL_DSTR | LITERAL_SSTR))? ('as' IDENTIFIER)? )?
 *      ;
 */
void _traverse_import_statement(ast_import_statement_t* node) {
    TRAVERSE_ENTER;

    // imports are handled during parsing. this should probably never be called.
    _traverse_compound_name(node->compound_name);
    if(node->str != NULL)
        _traverse_string_literal(node->str);
    _traverse_identifier(node->identifier);
    RETURN();
}
