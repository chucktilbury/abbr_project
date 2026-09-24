
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
void _traverse_formatted_string(ast_formatted_string_t* node) {
    TRAVERSE_ENTER;

    SHOW_STRING(node->literal_str);
    _traverse_formatted_string_param_list(node->params);

    RETURN();
}
