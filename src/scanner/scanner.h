#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "tokens.h"

void create_scanner(void);
void destroy_scanner(void);

token_t* scan_token(void);

void scanner_error(const char* fmt, ...);
void scanner_warning(const char* fmt, ...);
void scanner_fatal(const char* fmt, ...);

#endif /* _SCANNER_H_ */
