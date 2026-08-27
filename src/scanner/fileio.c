
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "fileio.h"

typedef struct _file_t {
    FILE* fp;
    string_t* fname;
    int line_no;
    int col_no;
    int crnt_char;
    struct _file_t* next;
} file_t;

static file_t* file_stack = NULL;

void open_file(string_t* fname) {

    file_t* ptr = _ALLOC_TYPE(file_t);
    ptr->fp = fopen(raw_string(fname), "r");
    if(ptr->fp == NULL) {
        fprintf(stderr, "fatal error: cannot open input file: \"%s\": %s", raw_string(fname), strerror(errno));
        exit(1);
    }
    ptr->fname = copy_string(fname);
    ptr->line_no = 1;
    ptr->col_no = 1;
    ptr->crnt_char = fgetc(ptr->fp);

    if(file_stack != NULL)
        ptr->next = file_stack;
    file_stack = ptr;
}

void close_file(void) {
    // if there is no file, fail silently
    if(file_stack != NULL) {
        file_t* tmp = file_stack;
        file_stack = tmp->next;

        fclose(tmp->fp);
        destroy_string(tmp->fname);
        _FREE(tmp);
    }
}

int get_char(void) {
    if(file_stack != NULL)
        return file_stack->crnt_char;
    else
        return EOF;
}

int consume_char(void) {
    if(file_stack != NULL) {
        if(file_stack->crnt_char != EOF) {
            if(file_stack->crnt_char == '\n') {
                file_stack->line_no++;
                file_stack->col_no = 1;
            }
            else
                file_stack->col_no++;

            file_stack->crnt_char = fgetc(file_stack->fp);
        }

        return file_stack->crnt_char;
    }
    else
        return EOF;
}

string_t* get_file_name(void) {
    if(file_stack != NULL)
        return file_stack->fname;
    else
        return NULL;
}

int get_line_no(void) {
    if(file_stack != NULL)
        return file_stack->line_no;
    else
        return -1;
}

int get_col_no(void) {
    if(file_stack != NULL)
        return file_stack->col_no;
    else
        return -1;
}

