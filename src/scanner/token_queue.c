
/*
    The pattern for using this supports the fact that the parser will try
    several paths before finding a match. So a stream of tokens may be
    examined more than once before being accepted into a valid rule. When
    a rule is accepted, then the tokens that created it are "flushed" and
    the memory that was allocated to them is freed.
 */
#include "token_queue.h"
#include "scanner.h"
#include "fileio.h"

typedef struct _token_list_t {
    token_t* tok;
    struct _token_list_t* next;
    struct _token_list_t* prev;
} token_list_t;

typedef struct _token_queue_t {
    token_list_t* first;
    token_list_t* last;
    token_list_t* crnt;
    pointer_list_t* pstk;
    int nitems;
} token_queue_t;

static token_queue_t* tqueue = NULL;

static inline token_list_t* create_token_list_elem(token_t* tok) {
    token_list_t* ptr = _ALLOC_TYPE(token_list_t);
    ptr->tok = tok;
    return ptr;
}

static inline void destroy_token_list_elem(token_list_t* ptr) {

    if(ptr != NULL) {
        destroy_token(ptr->tok);
        _FREE(ptr);
    }
}

static inline token_list_t* _append(token_t* tok) {

    token_list_t* ptr = create_token_list_elem(tok);

    if(tqueue->last != NULL) {
        tqueue->last->next = ptr;
        ptr->prev = tqueue->last;
        tqueue->last = ptr;
        tqueue->crnt = ptr;
        tqueue->nitems++;
    }
    else {
        tqueue->first = ptr;
        tqueue->last = ptr;
        tqueue->crnt = ptr;
        tqueue->nitems = 1;
    }

    return ptr;
}

static inline token_t* _tok(void) {
    if(tqueue->crnt != NULL)
        return tqueue->crnt->tok;
    else
        return NULL;
}

void create_token_queue(string_t* fname) {
    tqueue = _ALLOC_TYPE(token_queue_t);
    tqueue->pstk = create_ptr_list();
    open_file(fname);
    create_scanner();
    consume_token();
    mark_token_queue();
}

void destroy_token_queue(void) {

    if(tqueue != NULL) {
        destroy_ptr_list(tqueue->pstk);
        token_list_t* next;
        for(token_list_t* ptr = tqueue->first; ptr != NULL; ptr = next) {
            next = ptr->next;
            destroy_token(ptr->tok);
            _FREE(ptr);
        }
        _FREE(tqueue);
        tqueue = NULL;
    }
}

token_t* get_token(void) {
    return _tok();
}

token_t* consume_token(void) {
    if(tqueue->crnt != NULL) {
        if(tqueue->crnt->next == NULL)
            tqueue->crnt = _append(scan_token());
        else
            tqueue->crnt = tqueue->crnt->next;
    }
    else
        tqueue->crnt = _append(scan_token());

    return _tok();
}

void mark_token_queue(void) {
    push_ptr_list(tqueue->pstk, tqueue->crnt);
}

void reset_token_queue(void) {
    tqueue->crnt = peek_ptr_list(tqueue->pstk);
    pop_ptr_list(tqueue->pstk);
}

/*
 * Delete from the crnt pointer to the beginning of the queue.
 *
 * We could just set the "first" pointer and trust the GC to do the rest,
 * but prefer to go through the motions, even though it's a noop for the GC.
 */
void flush_token_queue(void) {

    token_list_t* prev;
    for(token_list_t* ptr = tqueue->crnt->prev; ptr != NULL; ptr = prev) {
        prev = ptr->prev;
        ptr->prev = NULL;
        destroy_token_list_elem(ptr);
        tqueue->nitems--;
    }

    tqueue->first = tqueue->crnt;
    tqueue->first->prev = NULL;
    pop_ptr_list(tqueue->pstk);
}

int token_queue_size(void) {
    return tqueue->nitems;
}

void print_token_queue(void) {

    printf("\n------- token queue nitems: %d -------\n", tqueue->nitems);
    for(token_list_t* ptr = tqueue->first; ptr != NULL; ptr = ptr->next) {
        print_token(ptr->tok);
        if(ptr == tqueue->crnt)
            printf("   ^^^ crnt ^^^\n");
    }
}
