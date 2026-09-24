
#include "symbols.h"

/**
 * @brief Create a symbol object
 * 
 * @param name 
 * @param type 
 * @param parent 
 * @param obj 
 * @return symbol_t* 
 */
symbol_t* create_symbol(string_t* name, symbol_class_t class, symbol_type_t type, sym_context_t* parent, void * obj) {
    ENTER;

    symbol_t* ptr = _ALLOC_TYPE(symbol_t);

    ptr->name = copy_string(name);
    ptr->class = class;
    ptr->type = type;
    ptr->parent = parent;
    ptr->obj = obj;

    switch(class) {
        case SYM_CLASS_NAMESPACE:
        case SYM_CLASS_CLASS:
        case SYM_CLASS_FUNCTION:
        case SYM_CLASS_INHERITANCE: // objects are built at runtime
            ptr->children = create_sym_context(parent);
            break;
        case SYM_CLASS_PARAMETER:
        case SYM_CLASS_OBJECT:
        case SYM_CLASS_OTHER:
        default:
            ptr->children = NULL;
            break;
    }

    RETURN(ptr);
}

/**
 * @brief Destroy a symbol objected
 * 
 * @param sym 
 */
void destroy_symbol(symbol_t* sym) {
    ENTER;
    if(sym != NULL) {
        destroy_string(sym->name);
        if(sym->children != NULL)
            destroy_sym_context(sym->children);
        _FREE(sym);
    }
    RETURN();
}

/**
 * @brief Create a symbol context object
 * 
 * @return sym_context_t* 
 */
sym_context_t* create_sym_context(sym_context_t* parent) {
    ENTER;

    sym_context_t* ptr = _ALLOC_TYPE(sym_context_t);

    ptr->parent = parent;
    ptr->children = create_hashtable();

    RETURN(ptr);
}

/**
 * @brief Destroy a symbol context object
 * 
 * @param ptr 
 */
void destroy_sym_context(sym_context_t* ptr) {
    ENTER;
    
    if(ptr != NULL) {
        int mark = 0;
        if(ptr->children != NULL) {
            for(symbol_t* sym = iterate_hashtable(ptr->children, &mark); sym!= NULL; 
                    sym = iterate_hashtable(ptr->children, &mark)) {
                destroy_symbol(sym);
            }
            destroy_hashtable(ptr->children);
        }
        _FREE(ptr);
    }

    RETURN();
}

/**
 * @brief Create a new symbol context and push it on the context stack.
 * 
 * @param scs 
 */
void push_sym_context(sym_ctx_stack_t* scs) {
    ENTER;

    // separate these for debugging
    sym_context_t* parent = peek_sym_context(scs);
    sym_context_t* ptr = create_sym_context(parent);
    push_ptr_list(scs, ptr);

    RETURN();
}

/**
 * @brief Remove the symbol context on the top of stack and return it.
 * 
 * @param scs 
 * @return sym_context_t* 
 */
sym_context_t* pop_sym_context(sym_ctx_stack_t* scs) {
    ENTER;
    
    sym_context_t* ptr = (sym_context_t*)pop_ptr_list(scs);

    RETURN(ptr);
}

/**
 * @brief Return the symbol context on the top of stack.
 * 
 * @param scs 
 * @return sym_context_t* 
 */
sym_context_t* peek_sym_context(sym_ctx_stack_t* scs) {
    ENTER;
    
    sym_context_t* ptr = (sym_context_t*)peek_ptr_list(scs);

    RETURN(ptr);
}

/**
 * @brief Add a created symbol into the given context.
 * 
 * @param ctx 
 * @param ptr 
 */
void add_symbol_to_context(sym_context_t* ctx, symbol_t* ptr) {
    ENTER;
    insert_hashtable(ctx->children, raw_string(ptr->name), (void*)ptr);
    RETURN();
}

/**
 * @brief Recursively find a symbol in the context tree. Returns a point to
 * the symbol or NULL if it's not found.
 * 
 * @param ctx 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* search_symbol_fragment(sym_context_t* ctx, string_t* name) {
    ENTER;
    symbol_t* ptr = NULL;
    RETURN(ptr);    
}

/**
 * @brief Search the symbol tree for the root name to validate it's existence 
 * and type. If there is a reference to a function or an array in the list, 
 * then it must be partially validated, since the types cannot be fully known. 
 * 
 * @param ctx 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* search_symbol_reference(sym_context_t* ctx, string_list_t* name) {
    ENTER;
    symbol_t* ptr = NULL;
    RETURN(ptr);        
}

/**
 * @brief Returns a pointer to the symbol in the given context. Does not 
 * recurse. If the symbol is present, then return a pointer to it, or NULL 
 * if it cannot be located.
 * 
 * @param ctx 
 * @param name 
 * @return symbol_t* 
 */
symbol_t* symbol_in_context(sym_context_t* ctx, string_t* name) {
    ENTER;
    symbol_t* ptr = (symbol_t*)find_hashtable(ctx->children, raw_string(name));
    RETURN(ptr);    
}

/**
 * @brief Write the symbol tree to a DOT file for conversion into a tree 
 * graphic. Expects the ctx to be a pointer to the root context.
 * 
 * @param fname 
 * @param ctx 
 */
void symbols_to_dotfile(string_t* fname, sym_context_t* ctx) {
    ENTER;
    RETURN();
}


