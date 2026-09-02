
#include <stdio.h>
#include "expression.h"
#include "ast_node.h"
#include "tree_to_dot.h"
#include "solver.h"

token_t token_list[] = {
    { TOK_LPAREN, "(" },
    { TOK_OPERAND, "2.0" },
    { TOK_POW, "^" },
    { TOK_OPERAND, "3.5" },
    { TOK_MUL, "*" },
    { TOK_LPAREN, "(" },
    { TOK_SUB, "-" },
    { TOK_OPERAND, "5.0" },
    { TOK_ADD, "+" },
    { TOK_OPERAND, "7.125" },
    { TOK_RPAREN, ")" },
    { TOK_DIV, "/" },
    { TOK_OPERAND, "9.5" },
    { TOK_RPAREN, ")" },
    { -1, NULL },
};

void print_token_list(token_t* list) {

    printf("expression:\n    ");
    for(int i = 0; list[i].text != NULL; i++)
        printf("%s", list[i].text);
    printf("\n");
}

int main(void) {

    // printf("%s\n", exp1);
    print_token_list(token_list);
    ast_node_t* tree = infix_to_tree(token_list);

    printf("\n(%f)\n", solver(tree));
    composer(tree);

    FILE* fp = fopen("test.dot", "w");
    write_dot_file(tree, fp);

    return 0;
}
