#ifndef _TOKEN_H_
#define _TOKEN_H_

typedef enum {
    TOK_OPERAND = 256,
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_MOD,
    TOK_POW,
    // implied in the tree
    TOK_LPAREN,
    TOK_RPAREN,
    // comparisons
    TOK_EQU,
    TOK_NEQU,
    TOK_LT,
    TOK_GT,
    TOK_LTE,
    TOK_GTE,
    TOK_NOT,
    TOK_AND,
    TOK_OR,
    // these are set by the parser
    TOK_UMINUS,
    TOK_UPLUS,
} token_type_t;

typedef struct {
    token_type_t type;
    const char* text;
} token_t;


#endif /* _TOKEN_H_ */
