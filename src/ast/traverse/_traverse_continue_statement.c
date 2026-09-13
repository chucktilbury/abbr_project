
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  continue_statement
 *      : 'continue'
 *      ;
 */
void _traverse_continue_statement(ast_continue_statement_t* node) {
    TRAVERSE_ENTER;
    (void)node;
    RETURN();
}
