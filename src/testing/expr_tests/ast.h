#ifndef _AST_H_
#define _AST_H_

#include "token.h"

typedef enum {
    OPER_ADD = TOK_ADD,
    OPER_SUB = TOK_SUB,
    OPER_MUL = TOK_MUL,
    OPER_DIV = TOK_DIV,
    OPER_MOD = TOK_MOD,
    OPER_POW = TOK_POW,
    OPER_UMINUS = TOK_UMINUS,
    OPER_UPLUS = TOK_UPLUS,
    OPER_EQU = TOK_EQU,
    OPER_NEQU = TOK_NEQU,
    OPER_LT = TOK_LT,
    OPER_GT = TOK_GT,
    OPER_LTE = TOK_LTE,
    OPER_GTE = TOK_GTE,
    OPER_NOT = TOK_NOT,
    OPER_AND = TOK_AND,
    OPER_OR = TOK_OR,
    OPER_LPAREN,
} oper_type_t;

typedef enum {
    AST_VALUE,
    AST_OPERATOR,
    // place holder while solving
    AST_LPAREN,
} ast_type_t;

typedef struct _ast_node_t {
    ast_type_t type;
} ast_node_t;

typedef struct _ast_value_t {
    ast_node_t node;
    float value;
} ast_value_t;

typedef struct _ast_operator_t {
    ast_node_t node;
    oper_type_t oper;
    int is_unary;
    struct _ast_node_t* left;
    struct _ast_node_t* right;
} ast_operator_t;

typedef struct _ast_lparen_oper_t {
    ast_node_t node;
} ast_lparen_oper_t;


#endif /* _AST_H_ */
