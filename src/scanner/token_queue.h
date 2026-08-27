#ifndef _TOKEN_QUEUE_H_
#define _TOKEN_QUEUE_H_

#include "common.h"
#include "tokens.h"

void create_token_queue(string_t* fname);
void destroy_token_queue(void);

token_t* get_token(void);
token_t* consume_token(void);

void mark_token_queue(void);
void reset_token_queue(void);
void flush_token_queue(void);

void print_token_queue(void);

#endif /* _TOKEN_QUEUE_H_ */
