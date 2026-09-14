
/*
    This AST pass does nothing but traverse the tree and print relevent trace
    information if it's enabled. It is one big file because it's intended to
    be used as a template, copied and edited to actually contain useful
    functionality. The parser returns a pointer to the tree.
*/

#include "traverse.h"
#include "ast.h"
#include "common.h"

/*
 * Main entry point for AST traverse
 */
void traverse_ast(ast_node_t* node) {
    TRAVERSE_ENTER;
    LEGEND("BEGIN TRAVERSE");
    _traverse_module((ast_module_t*)node);
    LEGEND("END TRAVERSE");
    RETURN();
}
