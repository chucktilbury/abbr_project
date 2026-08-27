
#include "alloc.h"
#include "error.h"
#include "int_list.h"


int_list_t* create_int_list(void) {

    int_list_t* ptr = _ALLOC_TYPE(int_list_t);
    ptr->len = 0;
    ptr->cap = 8;
    ptr->buffer = _ALLOC_ARRAY(int, ptr->cap);

    return ptr;
}

void destroy_int_list(int_list_t* lst) {

    if(lst) {
        _FREE(lst->buffer);
        _FREE(lst);
    }
}

void append_int_list(int_list_t* lst, int val) {

    if(lst->len+1 > lst->cap) {
        lst->cap <<= 1;
        lst->buffer = _REALLOC_ARRAY(lst->buffer, int, lst->cap);
    }

    lst->buffer[lst->len] = val;
    lst->len++;
}

void push_int_list(int_list_t* lst, int val) {

    append_int_list(lst, val);
}

void pop_int_list(int_list_t* lst) {

    if(lst->len > 0) {
        lst->len--;
    }
}

int peek_int_list(int_list_t* lst) {

    int val;

    if(lst->len > 0)
        val = lst->buffer[lst->len-1];
    else
        val = lst->buffer[0];

    return val;
}

void clear_int_list(int_list_t* lst) {

    lst->len = 0;
}

int index_int_list(int_list_t* lst, int index) {

    int val;

    if(index > 0 && index < lst->len)
        val = lst->buffer[index];
    else
        val = lst->buffer[0];

    return val;
}

int iterate_int_list(int_list_t* lst, int* mark) {

    int val;

    if(*mark > 0 && *mark < lst->len) {
        val = lst->buffer[*mark];
        *mark = *mark + 1;
    }
    else
        FATAL("invalid index");

    return val;
}

