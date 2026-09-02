#ifndef _AST_NODE_H_
#define _AST_NODE_H_

#include "ast.h"

typedef struct {
    ast_node_t** list;
    int cap;
    int len;
} ast_node_list_t;

ast_node_list_t* create_ast_node_list(void);
void destroy_ast_node_list(ast_node_list_t* ptr);
void append_ast_node_list(ast_node_list_t* ptr, ast_node_t* item);
void push_ast_node_list(ast_node_list_t* ptr, ast_node_t* item);
ast_node_t* pop_ast_node_list(ast_node_list_t* ptr);
ast_node_t* peek_ast_node_list(ast_node_list_t* ptr);
ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, int* post);
ast_node_t* index_ast_node_list(ast_node_list_t* lst, int index);

ast_node_t* create_ast_node(ast_type_t type);
void destroy_ast_node(ast_node_t* ptr);
void print_ast_node_list(ast_node_list_t* lst);
const char* ast_type_to_str(ast_node_t* node);

#endif /* _AST_NODE_H_ */
