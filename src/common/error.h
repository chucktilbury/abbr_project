#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef USE_ASSERT
#define ASSERT(e, ...)                                                               \
    do {                                                                             \
        if(!(e)) {                                                                   \
            fprintf(stderr, "assert failed: %s:%d: (%s): ", __PRETTY_FUNCTION__, __LINE__, #e); \
            fprintf(stderr, __VA_ARGS__);                                            \
            fputc('\n', stderr);                                                     \
            abort();                                                                 \
        }                                                                            \
    } while(0)
#else
#define ASSERT(...)
#endif

#define FATAL(...)                                                   \
    do {                                                             \
        fprintf(stderr, "fatal error: %s:%s:%d: ", __FILE__, __PRETTY_FUNCTION__, __LINE__); \
        fprintf(stderr, __VA_ARGS__);                                \
        fputc('\n', stderr);                                         \
        exit(1);                                                     \
    } while(0)

#define ERROR(...) \
    do{ \
        fprintf(stderr, "error: %s: %s(): %d: ", __FILE__, __PRETTY_FUNCTION__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fputc('\n', stderr); \
    } while(0)

#define WARNING(...) \
    do{ \
        fprintf(stderr, "warning: %s: %s(): %d: ", __FILE__, __PRETTY_FUNCTION__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
        fputc('\n', stderr); \
    } while(0)

#endif /* _ERROR_H_ */
