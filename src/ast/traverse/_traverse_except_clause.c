
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' IDENTIFIER)? ')' function_body
 *      ;
 */
void _traverse_except_clause(ast_except_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_name(node->compound_name);

    if(node->identifier != NULL) {
        _traverse_identifier(node->identifier);
    }

    _traverse_function_body(node->function_body);

    RETURN();
}

