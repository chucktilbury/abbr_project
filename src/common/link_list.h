#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

typedef struct _link_list_node_t {
    void* data;
    struct _link_list_node_t* prev;
    struct _link_list_node_t* next;
} link_list_node_t;

typedef struct _link_list_t {
    struct _link_list_node_t* first;
    struct _link_list_node_t* last;
    struct _link_list_node_t* crnt;
    int nitems;
} link_list_t;

link_list_t* create_link_list(void);
void destroy_link_list(link_list_t* lst);

void append_link_list(link_list_t* lst, void* data);
void prepend_link_list(link_list_t* lst, void* data);

void* get_link_list(link_list_t* lst);
void* next_link_list(link_list_t* lst);
void* prev_link_list(link_list_t* lst);

#endif /* _LINK_LIST_H_ */
