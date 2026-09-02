
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "to_string.h"

ast_node_list_t* create_ast_node_list(void) {
    ast_node_list_t* ptr = calloc(1, sizeof(ast_node_list_t));
    ptr->len = 0;
    ptr->cap = 0x01;
    ptr->list = calloc(ptr->cap, sizeof(ast_node_t*));

    return ptr;
}

void destroy_ast_node_list(ast_node_list_t* ptr) {
    if(ptr) {
        // do not destroy the pointers because they are in use.
        // for(int i = 0; i < ptr->len; i++)
        //     free(ptr->list[i]);
        free(ptr->list);
        free(ptr);
    }
}

void append_ast_node_list(ast_node_list_t* ptr, ast_node_t* item) {
    if(ptr->len + 1 > ptr->cap) {
        ptr->cap <<= 1;
        ptr->list = realloc(ptr->list, sizeof(ast_node_t*) * ptr->cap);
    }

    ptr->list[ptr->len] = item;
    ptr->len++;
}

void push_ast_node_list(ast_node_list_t* ptr, ast_node_t* item) {
    append_ast_node_list(ptr, item);
}

// returning the item that was popped. caller has to destroy it.
ast_node_t* pop_ast_node_list(ast_node_list_t* ptr) {
    if(ptr->len > 0) {
        ptr->len--;
        return ptr->list[ptr->len];
    }
    else
        return NULL;
}

ast_node_t* peek_ast_node_list(ast_node_list_t* ptr) {
    if(ptr->len > 0)
        return ptr->list[ptr->len - 1];
    else
        return NULL;
}

ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, int* post) {

    if(lst == NULL)
        return NULL;

    ast_node_t* ptr = NULL;

    if((*post >= 0) && (*post < lst->len)) {
        ptr = lst->list[*post];
        *post = *post + 1;
    }

    return ptr;
}

ast_node_t* index_ast_node_list(ast_node_list_t* lst, int index) {

    if(index >= 0 && index < lst->len)
        return lst->list[index];
    else
        return NULL;
}

ast_node_t* create_ast_node(ast_type_t type) {
    ast_node_t* ptr = NULL;
    switch(type) {
        case AST_VALUE:
            ptr = calloc(1, sizeof(ast_value_t));
            ptr->type = type;
            break;
        case AST_OPERATOR:
            ptr = calloc(1, sizeof(ast_operator_t));
            ptr->type = type;
            break;
        case AST_LPAREN:
            ptr = calloc(1, sizeof(ast_lparen_oper_t));
            ptr->type = type;
            break;
        default:
            fprintf(stderr, "unknown node type");
            exit(1);
    }

    return ptr;
}

void destroy_ast_node(ast_node_t* ptr) {
    if(ptr != NULL)
        free((void*)ptr);
}

const char* ast_node_to_str(ast_node_t* node) {

    static char buffer[256];

    memset(buffer, 0, sizeof(buffer));

    sprintf(buffer, "node type: %s\n", ast_type_to_str(node));
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

void print_ast_node_list(ast_node_list_t* lst) {

    printf("\nprint ast node list:\n");
    printf("   list cap %d: list len %d\n", lst->cap, lst->len);
    for(int i = 0; i < lst->len; i++) {
        printf("%s\n", ast_node_to_str(lst->list[i]));
        // ast_node_t* node = lst->list[i];
        // printf("   type %s ", ast_type_to_str(node));
        // if(node->type == AST_OPERATOR) {
        //     printf("   type %s", oper_type_to_str((ast_operator_t*)node));
        // }
        // else if(node->type == AST_VALUE) {
        //     printf("   value %f", ((ast_value_t*)node)->value);
        // }
        // else
        //     printf("   >>>>> something else");
        // printf("\n");
    }
}
