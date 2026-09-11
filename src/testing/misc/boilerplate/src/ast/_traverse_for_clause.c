
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? IDENTIFIER)? )? ')' )? loop_body
 *      ;
 */
void _traverse_for_clause(ast_for_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->identifier != NULL) {
        _traverse_identifier(node->identifier);
    }

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    if(node->type_specifier != NULL) {
        _traverse_type_specifier(node->type_specifier);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}

