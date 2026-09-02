#ifndef _TREE_TO_DOT_H_
#define _TREE_TO_DOT_H_

#include "ast_node.h"

void write_dot_file(ast_node_t* tree, FILE* outfp);

#endif /* _TREE_TO_DOT_H_ */
