#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include "token.h"
#include "ast_node.h"

ast_node_t* infix_to_tree(token_t* token_list);

#endif /* _EXPRESSION_H_ */
