#ifndef _TRACE_H_
#define _TRACE_H_

#ifdef USE_TRACE
// extern int verbosity;
// extern int level;
#define DEBUG_TRACE_LEVEL 50

#define INDENT indent()

#define ENTER                                                                   \
    do {                                                                        \
        if(peek_verbosity() >= DEBUG_TRACE_LEVEL) {                                        \
            INDENT;                                                             \
            printf("%s %s()\n", colorize(fgYEL, aBOLD, 0, "ENTER:"), __func__); \
            inc_level();                                                            \
        }                                                                       \
    } while(false)

#define RETURN(...)                                                                               \
    do {                                                                                          \
        if(peek_verbosity() >= DEBUG_TRACE_LEVEL) {                                                          \
            dec_level();                                                                              \
            INDENT;                                                                               \
            printf("%s %s()\n", colorize(fgYEL, aBOLD, 0, "RETURN(%s)", #__VA_ARGS__), __func__); \
        }                                                                                         \
        return __VA_ARGS__;                                                                       \
    } while(false)

#define TRACE(...)                                              \
    do {                                                        \
        if(peek_verbosity() >= DEBUG_TRACE_LEVEL) {                        \
            INDENT;                                             \
            printf("%s", colorize(fgCYA, aBOLD, 0, "TRACE: ")); \
            printf(__VA_ARGS__);                                \
            fputc('\n', stdout);                                \
        }                                                       \
    } while(false)

#define TRACEX(n, ...)                                     \
    do {                                                   \
        if(peek_verbosity() >= (n)) {                             \
            INDENT;                                        \
            printf("\x1b[1;36mTRACE:\x1b[m " __VA_ARGS__); \
            fputc('\n', stdout);                           \
        }                                                  \
    } while(false)


#define LEGEND(s) \
    do { \
        if(peek_verbosity() >= DEBUG_TRACE_LEVEL) \
            print_legend(s); \
    } while(0)

void print_legend(const char* str);
void prnch(int ch);

//#include "string_buffer.h"
void prnstr(const char* str);
void trace_pad(int num, int ch);
void indent(void);
void inc_level(void);
void dec_level(void);

void push_verbosity(int val);
void pop_verbosity(void);
int peek_verbosity(void);

#else

#define ENTER
#define RETURN(...)         \
    do {                    \
        return __VA_ARGS__; \
    } while(false)
#define TRACE(...)
#define TRACEX(n, ...)
#define LEGEND(s)
#endif

#endif /* _TRACE_H_ */
