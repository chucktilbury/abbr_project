#ifndef _FIND_FILE_H_
#define _FIND_FILE_H_

#include "string_buffer.h"

string_t* find_file(const char* fname);
void add_dir_to_search(string_t* str);
void setup_env(void);

#endif /* _FIND_FILE_H_ */
