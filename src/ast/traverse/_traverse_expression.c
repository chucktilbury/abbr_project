
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  expression
 *      : expression ('*' | '/' | '%') expression
 *      | expression '^' expression
 *      | expression ('+' | '-') expression
 *      | expression ('<' | '>' | '<=' | '>=' | 'lt' | 'gt' | 'lte' | 'gte') expression
 *      | expression ('==' | '!=' | 'equ' | 'neq' ) expression
 *      | expression ('&&' | 'and') expression
 *      | expression ('||' | 'or') expression
 *      | ('!' | 'not' | '-') expression
 *      | '(' expression ')'
 *      | primary_expression
 *      ;
 */
void _traverse_expression(ast_expression_t* node) {
    TRAVERSE_ENTER;

    // TBD-- this will certainly change
    (void)node;

    RETURN();
}

