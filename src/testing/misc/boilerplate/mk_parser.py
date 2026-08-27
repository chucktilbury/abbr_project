#!/usr/bin/python3

import sys, os
from string import Template
import re

dest_dir = "./src/parser/"
################################################################
parse_header_begin = '''
/*
 * This is a generated file
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include "common.h"
#include "ast.h"

typedef enum {
    PMODE_NORMAL,
    PMODE_INCLUDE,
    PMODE_IMPORT,
} parser_mode_t;

typedef enum {
    PSCOPE_PRIVATE,
    PSCOPE_PUBLIC,
    PSCOPE_PROTECTED,
} parser_scope_t;

typedef enum {
    START_STATE,
    RETURN_MATCH,
    RETURN_NO_MATCH,
    RETURN_ERROR,
} parser_state_t;

typedef struct _parser_state_t {
    int_list_t* mode_stack;
    int_list_t* scope_stack;
    int errors;
    int warnings;
} parser_context_t;

ast_node_t* parse(void);
parser_context_t* create_parser_context(void);
void push_parser_scope(parser_context_t* context, parser_scope_t scope);
void pop_parser_scope(parser_context_t* context);
parser_scope_t peek_parser_scope(parser_context_t* context);
void push_parser_mode(parser_context_t* context, parser_mode_t mode);
void pop_parser_mode(parser_context_t* context);
parser_mode_t peek_parser_mode(parser_context_t* context);
void recover_parser_error(parser_context_t* context);

void parser_error(parser_context_t* context, const char* fmt, ...);
void parser_warning(parser_context_t* context, const char* fmt, ...);

'''

################################################################
parser_func_template = '''
$ast_name* _parse_$name(parser_context_t* context);'''

################################################################
parse_header_end = '''

#ifdef USE_TRACE
#define TRACE_STATE \\
    do { \\
        if(verbosity >= DEFAULT_TRACE) { \\
            INDENT; \\
            printf("%s: %d\\n", colorize(fgCYA, aBOLD, 0, "STATE: "), state); \\
        } \\
    } while(0)
#else
#define TRACE_STATE
#endif

#endif /* _PARSER_H_ */


'''

################################################################
parser_src_begin = '''
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
    ast_node_t* node = (ast_node_t*)_parse_$first(context);
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

'''
################################################################
parse_file = '''
/*
 * this is a generated file
 */
#include "common.h"
#include "parser.h"
#include "ast.h"
#include "token_queue.h"

/*
$rule */
$ast_name* _parse_$name(parser_context_t* context) {

    ENTER;
    $ast_name* node = NULL;
    // ast elements here

    int finished = 0;
    int state = START_STATE;
    mark_token_queue();

    while(!finished) {
        switch(state) {
            case START_STATE: {
                TRACE_STATE;
            } break;

            case RETURN_MATCH: {
                TRACE_STATE;
                node = ($ast_name*)create_ast_node($ast_marker);
                // ast elements here
                flush_token_queue();
            } break;

            case RETURN_NO_MATCH: {
                TRACE_STATE;
                reset_token_queue();
            } break;

            case RETURN_ERROR: {
                TRACE_STATE;
                recover_parser_error(context);
            } break;

            default:
                FATAL("invalid state: %d", state);
        }
    }

    RETURN(node);
}

'''

################################################################
def get_grammar(name):
    grammar = []
    with open(name, "r") as fp:
        for line in fp:
            tmp = {}
            line = line.strip()
            sr = re.search(r"^[_a-zA-Z][_a-zA-Z0-9]*", line)
            if sr:
                tmp['name'] = sr[0]
                tmp['body'] = []
                for l in fp:
                    l = l.strip()
                    if len(l) > 0:
                        tmp['body'].append(l)
                    else:
                        break;


                grammar.append(tmp)
    return grammar

################################################################
def make_rule(item):
    s = " *  "+item['name']+"\n"
    for x in item['body']:
        s += " *      "+x+"\n"

    return s

################################################################
def mk_dirs():
    if(not os.path.isdir("./src")):
        os.mkdir("./src")

    if(not os.path.isdir("./src/parser")):
        os.mkdir("./src/parser")

################################################################
def mk_parser_header(grammar):
    with open(dest_dir+"parser.h", "w") as fp:
        fp.write(parse_header_begin)

        tmp = Template(parser_func_template)
        for x in grammar:
            fp.write(tmp.substitute({'name': x['name'], 'ast_name':"ast_"+x['name']+"_t"}))

        fp.write(parse_header_end)

def mk_parser_src(grammar):
    tmp = Template(parser_src_begin)
    with open(dest_dir+"parser.c", "w") as fp:
        fp.write(tmp.substitute({'first': grammar[0]['name']}))

    for item in grammar:
        with open(dest_dir+"_parse_"+item['name']+".c", "w") as fp:
            tmp = Template(parse_file)
            fp.write(tmp.substitute({
                'name': item['name'],
                'rule': make_rule(item),
                'ast_name': "ast_"+item['name']+"_t",
                'ast_marker': "AST_"+item['name'].upper()
            }))




g = get_grammar("simple.txt")
mk_dirs()
mk_parser_header(g)
mk_parser_src(g)
