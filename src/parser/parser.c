
/*
 * this is a generated file
 */

#include "parser.h"
#include "ast.h"
#include "common.h"
#include "token_queue.h"
#include "trace.h"
#include <stdarg.h>

parser_context_t* parse(void) {
    ENTER;
    LEGEND("START PARSER");

    create_token_queue(get_cmd_opt("files"));
    parser_context_t* context = create_parser_context();
    push_parser_mode(context, PMODE_NORMAL);
    context->tree = (ast_node_t*)_parse_module(context);

    LEGEND("END PARSER");
    RETURN(context);
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

void touch_context(parser_context_t* context) {

    context->fname = raw_string(get_file_name());
    context->line = get_line_no();
    context->col = get_col_no();
}

void parser_error(parser_context_t* context, const char* fmt, ...) {

    //fprintf(stderr, "error: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());
    fprintf(stderr, "error: %s: %d: %d: ", context->fname, context->line, context->col);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    context->errors++;
}

void parser_warning(parser_context_t* context, const char* fmt, ...) {

    fprintf(stderr, "warning: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    context->warnings++;
}

const char* parser_state_to_str(int state) {

    static char buffer[64];
    memset(buffer, 0, sizeof(buffer));
    if(state >= START_STATE && state < REPEAT_STATE) {
        if(state - START_STATE != 0)
            sprintf(buffer, "START_STATE+%d", state-START_STATE);
        else
            sprintf(buffer, "START_STATE");
    }
    else if(state >= REPEAT_STATE && state < RETURN_MATCH) {
        if(state - REPEAT_STATE != 0)
            sprintf(buffer, "REPEAT_STATE+%d", state-REPEAT_STATE);
        else
            sprintf(buffer, "REPEAT_STATE");
    }
    else if(state >= RETURN_MATCH && state < RETURN_NO_MATCH) {
        if(state - RETURN_MATCH != 0)
            sprintf(buffer, "RETURN_MATCH+%d", state-REPEAT_STATE);
        else
            sprintf(buffer, "RETURN_MATCH");
    }
    else if(state >= RETURN_NO_MATCH && state < RETURN_ERROR) {
        if(state - RETURN_NO_MATCH != 0)
            sprintf(buffer, "RETURN_NO_MATCH+%d", state-REPEAT_STATE);
        else
            sprintf(buffer, "RETURN_NO_MATCH");
    }
    else if(state >= RETURN_ERROR && state < USER_STATE) {
        if(state - RETURN_ERROR != 0)
            sprintf(buffer, "RETURN_ERROR+%d", state-REPEAT_STATE);
        else
            sprintf(buffer, "RETURN_ERROR");
    }
    else {
        if(state - USER_STATE != 0)
            sprintf(buffer, "USER_STATE+%d", state-USER_STATE);
        else
            sprintf(buffer, "USER_STATE");
    }
    return buffer;
}

