#ifndef _SYMBOLS_H_ 
#define _SYMBOLS_H_

#include "common.h"
#include <stdbool.h>

typedef enum {
    SYM_CLASS_NAMESPACE,
    SYM_CLASS_CLASS,
    SYM_CLASS_INHERITANCE,
    SYM_CLASS_FUNCTION,
    SYM_CLASS_PARAMETER,
    SYM_CLASS_OBJECT,
    SYM_CLASS_OTHER,
} symbol_class_t;

typedef enum {
    SYM_TYPE_INTEGER,
    SYM_TYPE_UNSIGNED,
    SYM_TYPE_BOOL,
    SYM_TYPE_STRING,
    SYM_TYPE_DICT,
    SYM_TYPE_LIST,
    SYM_TYPE_FLOAT,
    SYM_TYPE_OBJECT,
    SYM_TYPE_OTHER,
} symbol_type_t;

typedef struct _sym_context_t {
    struct _sym_context_t* parent;  // pointer to the context that owns this one.
    hash_table_t* children;         // symbols that this context owns
} sym_context_t;

typedef struct _symbol_t {
    string_t* name;         // searchable name
    symbol_class_t class;   // namespace, class, etc
    symbol_type_t type;     // normally an object.
    void * obj;             // pointer to the thing the symbol defines
    sym_context_t* parent;  // the context that this symbol belongs to
    sym_context_t* children;// the context that this symbol owns, if any
} symbol_t;

typedef pointer_list_t sym_ctx_stack_t;

symbol_t* create_symbol(string_t* name, symbol_class_t class, symbol_type_t type, sym_context_t* parent, void * obj);
void destroy_symbol(symbol_t* sym);

void push_sym_context(sym_ctx_stack_t* scs);
sym_context_t* pop_sym_context(sym_ctx_stack_t* scs);
sym_context_t* peek_sym_context(sym_ctx_stack_t* scs);

sym_context_t* create_sym_context(sym_context_t* parent);
void destroy_sym_context(sym_context_t* ptr);
void add_symbol_to_context(sym_context_t* ctx, symbol_t* ptr);

symbol_t* search_symbol_fragment(sym_context_t* ctx, string_t* name);
symbol_t* search_symbol_reference(sym_context_t* ctx, string_list_t* name);
symbol_t* symbol_in_context(sym_context_t* ctx, string_t* name);

void symbols_to_dotfile(string_t* fname, sym_context_t* ctx);

#endif /* _SYMBOLS_H_ */

