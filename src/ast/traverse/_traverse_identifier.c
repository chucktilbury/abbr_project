
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  identifier
 *      : IDENTIFIER
 *      ;
 */
void _traverse_identifier(ast_identifier_t* node) {
    TRAVERSE_ENTER;
    SHOW_STRING(node->name);
    RETURN();
}
