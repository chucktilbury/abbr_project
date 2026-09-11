
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  break_statement
 *      : 'break'
 *      ;
 */
void _traverse_break_statement(ast_break_statement_t* node) {
    TRAVERSE_ENTER;
    (void)node;
    RETURN();
}

