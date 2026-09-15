
#include "common.h"
#include "int_list.h"

#ifdef USE_TRACE
// int verbosity = 0;
static int level = 0;

int_list_t* verbosity_stack = NULL;

void indent(void) {

    trace_pad(level*2, ' ');
}

void inc_level(void) {
    level++;
}

void dec_level(void) {
    level--;
}

void trace_pad(int num, int ch) {

    for(int i = 0; i < num; i++)
        putc(ch, stdout);
}

void print_legend(const char* str) {

    if(str != NULL) {
        int len = strlen(str);
        trace_pad((80 - (len + 2)) / 2, '-');
        cprintf(aBOLD, 0, 0, " %s ", str);
        trace_pad((80 - (len + 2)) / 2 + ((!(len & 0x01)) ? 0 : 1), '-');
        putc('\n', stdout);
    }
    else {
        trace_pad(80, '-');
        putc('\n', stdout);
    }
}

void prnch(int ch) {

    if(isprint(ch) && !isspace(ch))
        printf("%c", ch);
    else {
        cprintf(fgRED, aBOLD, 0, "%02X", ch);
    }
}

void prnstr(const char* str) {

    for(int i = 0; str[i] != '\0'; i++) {
        prnch(str[i]);
    }
}

void push_verbosity(int val) {

    if(verbosity_stack == NULL) 
        verbosity_stack = create_int_list();

    push_int_list(verbosity_stack, val);
}

void pop_verbosity(void) {

    pop_int_list(verbosity_stack);
}

int peek_verbosity(void) {

    return peek_int_list(verbosity_stack);
}


#endif
