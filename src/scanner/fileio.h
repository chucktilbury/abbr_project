#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "common.h"

void open_file(string_t* fname);
void close_file(void);

int get_char(void);
int consume_char(void);

string_t* get_file_name(void);
int get_line_no(void);
int get_col_no(void);

#endif /* _FILEIO_H_ */
