
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  literal_type
 *      : ('integer' | 'int')
 *      | ('boolean' | 'bool')
 *      | 'string'
 *      | 'dict'
 *      | 'list'
 *      | 'unsigned'
 *      | 'float'
 *      | 'nothing'
 *      ;
 */
void _traverse_literal_type(ast_literal_type_t* node) {
    TRAVERSE_ENTER;
    SHOW_TOKEN_TYPE(node->type);
    RETURN();
}
