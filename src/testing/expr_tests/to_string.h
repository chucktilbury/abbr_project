#ifndef _TO_STRING_H_
#define _TO_STRING_H_

#include "token.h"
#include "ast_node.h"

const char* tok_type_to_str(token_t* tok);
const char* ast_type_to_str(ast_node_t* node);
const char* oper_type_to_str(struct _ast_operator_t* node);

#endif /* _TO_STRING_H_ */
