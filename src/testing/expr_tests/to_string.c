
#include "to_string.h"

const char* tok_type_to_str(token_t* tok) {
    return (tok->type == TOK_OPERAND) ? "OPERAND" :
            (tok->type == TOK_ADD)    ? "ADD" :
            (tok->type == TOK_SUB)    ? "SUB" :
            (tok->type == TOK_MUL)    ? "MUL" :
            (tok->type == TOK_DIV)    ? "DIV" :
            (tok->type == TOK_MOD)    ? "MOD" :
            (tok->type == TOK_POW)    ? "POW" :
            (tok->type == TOK_LPAREN) ? "LPAREN" :
            (tok->type == TOK_RPAREN) ? "RPAREN" :
            (tok->type == TOK_EQU)    ? "EQU" :
            (tok->type == TOK_NEQU)   ? "NEQU" :
            (tok->type == TOK_LT)     ? "LT" :
            (tok->type == TOK_GT)     ? "GT" :
            (tok->type == TOK_LTE)    ? "LTE" :
            (tok->type == TOK_GTE)    ? "GTE" :
            (tok->type == TOK_NOT)    ? "NOT" :
            (tok->type == TOK_AND)    ? "AND" :
            (tok->type == TOK_OR)     ? "OR" :
            (tok->type == TOK_UMINUS) ? "UMINUS" :
            (tok->type == TOK_UPLUS)  ? "UPLUS" :
                                        "UNKNOWN";
}

const char* ast_type_to_str(ast_node_t* node) {
    return (node->type == AST_VALUE)     ? "VALUE" :
            (node->type == AST_OPERATOR) ? "OPERATOR" :
            (node->type == AST_LPAREN)   ? "LPAREN" :
                                           "UNKNOWN";
}

const char* oper_type_to_str(struct _ast_operator_t* node) {
    return (node->oper == OPER_ADD)     ? "ADD" :
            (node->oper == OPER_SUB)    ? "SUB" :
            (node->oper == OPER_MUL)    ? "MUL" :
            (node->oper == OPER_DIV)    ? "DIV" :
            (node->oper == OPER_MOD)    ? "MOD" :
            (node->oper == OPER_POW)    ? "POW" :
            (node->oper == OPER_UMINUS) ? "UMINUS" :
            (node->oper == OPER_UPLUS)  ? "UPLUS" :
            (node->oper == OPER_EQU)    ? "EQU" :
            (node->oper == OPER_NEQU)   ? "NEQU" :
            (node->oper == OPER_LT)     ? "LT" :
            (node->oper == OPER_GT)     ? "GT" :
            (node->oper == OPER_LTE)    ? "LTE" :
            (node->oper == OPER_GTE)    ? "GTE" :
            (node->oper == OPER_NOT)    ? "NOT" :
            (node->oper == OPER_AND)    ? "AND" :
            (node->oper == OPER_OR)     ? "OR" :
            (node->oper == OPER_LPAREN) ? "LPAREN" :
                                          "UNKNOWN";
}

