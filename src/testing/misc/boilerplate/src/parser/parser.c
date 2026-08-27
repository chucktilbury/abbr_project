
/*
 * this is a generated file
 */

#include <stdarg.h>
#include "common.h"
#include "parser.h"
#include "ast.h"

ast_node_t* parse(void) {
    ENTER;
    parser_context_t* context = create_parser_context();
    ast_node_t* node = (ast_node_t*)_parse_module(context);
    RETURN(node);
}

parser_context_t* create_parser_context(void) {
    parser_context_t* ptr = _ALLOC_TYPE(parser_context_t);
    ptr->mode_stack = create_int_list();
    ptr->scope_stack = create_int_list();

    return ptr;
}

void push_parser_scope(parser_context_t* context, parser_scope_t scope) {
    push_int_list(context->scope_stack, scope);
}

void pop_parser_scope(parser_context_t* context) {
    pop_int_list(context->scope_stack);
}

parser_scope_t peek_parser_scope(parser_context_t* context) {
    return peek_int_list(context->scope_stack);
}

void push_parser_mode(parser_context_t* context, parser_mode_t mode) {
    push_int_list(context->mode_stack, mode);
}

void pop_parser_mode(parser_context_t* context) {
    pop_int_list(context->mode_stack);
}

parser_mode_t peek_parser_mode(parser_context_t* context) {
    return peek_int_list(context->mode_stack);
}

void recover_parser_error(parser_context_t* context) {
    (void)context;
    // TBD
}

void parser_error(parser_context_t* context, const char* fmt, ...) {
    fprintf(stderr, "error: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    context->errors++;
}

void parser_warning(parser_context_t* context, const char* fmt, ...) {
    fprintf(stderr, "warning: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    context->warnings++;
}

