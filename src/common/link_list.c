
#include "link_list.h"
#include "alloc.h"

link_list_t* create_link_list(void) {

    // alloc clears the memory
    link_list_t* ptr = _ALLOC_TYPE(link_list_t);

    return ptr;
}

void destroy_link_list(link_list_t* lst) {

    if(lst != NULL) {
        link_list_node_t* crnt, *next;
        for(crnt = lst->first; crnt != NULL; crnt = next) {
            next = crnt->next;
            _FREE(crnt);
        }
        _FREE(lst);
    }
}

void append_link_list(link_list_t* lst, void* data) {

    link_list_node_t* ptr = _ALLOC_TYPE(link_list_node_t);
    ptr->data = data;
    if(lst->last != NULL) {
        lst->last->next = ptr;
        ptr->prev = lst->last;
        lst->last = ptr;
        lst->nitems++;
    }
    else {
        lst->first = ptr;
        lst->last = ptr;
        lst->crnt = ptr;
        lst->nitems = 1;
    }
}

void prepend_link_list(link_list_t* lst, void* data) {

    link_list_node_t* ptr = _ALLOC_TYPE(link_list_node_t);
    ptr->data = data;
    if(lst->first != NULL) {
        lst->first->prev = ptr;
        ptr->next = lst->first;
        lst->first = ptr;
        lst->nitems++;
    }
    else {
        lst->first = ptr;
        lst->last = ptr;
        lst->crnt = ptr;
        lst->nitems = 1;
    }
}

void* get_link_list(link_list_t* lst) {
    if(lst->crnt != NULL)
        return lst->crnt->data;
    else
        return NULL;
}

void* next_link_list(link_list_t* lst) {
    if(lst->crnt != NULL)
        lst->crnt = lst->crnt->next;
    return get_link_list(lst);
}

void* prev_link_list(link_list_t* lst) {
    if(lst->crnt != NULL)
        lst->crnt = lst->crnt->prev;
    return get_link_list(lst);
}

