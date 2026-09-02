
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree_to_dot.h"
#include "to_string.h"

const char* mk_node_value(ast_node_t* node) {

    static char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    if(node->type == AST_OPERATOR) {
        sprintf(&buffer[strlen(buffer)], "operator: %s", oper_type_to_str((ast_operator_t*)node));
    }
    else if(node->type == AST_VALUE) {
        sprintf(&buffer[strlen(buffer)], "value: %f", ((ast_value_t*)node)->value);
    }
    else
        sprintf(&buffer[strlen(buffer)], ">>>>> something else");
    return buffer;
}

#define LEFT_NODE(n) (((n)->type == AST_OPERATOR)? (((ast_operator_t*)(n))->left): NULL)
#define RIGHT_NODE(n) (((n)->type == AST_OPERATOR)? (((ast_operator_t*)(n))->right): NULL)

void write_line(ast_node_t* tree, FILE* fp) {

    char label[256];

    if(tree == NULL)
        return;

    snprintf(label, sizeof(label), "_%p", (void*)tree);
    fprintf(fp, "    %s [label=\"%s\"]\n", label, mk_node_value(tree));

    if(LEFT_NODE(tree) != NULL) {
        fprintf(fp, "    \"%s\" -> \"_%p\";\n", label, (void*)LEFT_NODE(tree));
    }

    if(RIGHT_NODE(tree) != NULL) {
        fprintf(fp, "    \"%s\" -> \"_%p\";\n", label, (void*)RIGHT_NODE(tree));
    }

    /* recurse */
    write_line(LEFT_NODE(tree), fp);
    write_line(RIGHT_NODE(tree), fp);
}

void write_dot_file(ast_node_t* tree, FILE* outfp) {

    /* header info */
    fprintf(outfp, "digraph G {\n");
    fprintf(outfp, "    graph [ordering=\"out\"];\n");

    /* recursively write tree to file */
    write_line(tree, outfp);

    /* housekeeping */
    fprintf(outfp, "}\n");
}

