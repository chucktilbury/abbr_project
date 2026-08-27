
#ifndef _INT_LIST_H_
#define _INT_LIST_H_

typedef struct _int_list_t {
    int* buffer;
    int len;
    int cap;
} int_list_t;

int_list_t* create_int_list(void);
void destroy_int_list(int_list_t* lst);
void append_int_list(int_list_t* lst, int val);
void push_int_list(int_list_t* lst, int val);
void pop_int_list(int_list_t* lst);
int peek_int_list(int_list_t* lst);
void clear_int_list(int_list_t* lst);
int index_int_list(int_list_t* lst, int index);
int iterate_int_list(int_list_t* lst, int* mark);

#endif /* _INT_LIST_H_ */
