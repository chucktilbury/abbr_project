
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 */
void _traverse_assignment(ast_assignment_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_reference(node->compound_reference);
    _traverse_expression(node->expression);

    RETURN();
}
