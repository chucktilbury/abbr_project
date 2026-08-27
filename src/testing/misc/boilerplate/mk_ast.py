#!/usr/bin/python3
# quick and dirty boilerplate

import os
from string import Template
import re

dest_dir = "./src/ast/"
################################################################
ast_struct = '''
/*
$rule */
typedef struct $local_name {
    ast_node_t node;

    // objects
} $public_name;

'''

################################################################
ast_header_header = '''
/*
 *  This is a generated file
 */
#ifndef _AST_H_
#define _AST_H_

//#include "tokens.h"

typedef enum {
'''

################################################################
ast_nodes = '''} ast_type_t;

typedef struct _ast_node_t {
    ast_type_t type;
    const char* fname;
    int line_no;
    int col_no;
} ast_node_t;

'''

################################################################
ast_header_protos = '''

ast_node_t* create_ast_node(ast_type_t type);
void traverse_ast(ast_node_t* node);
const char* node_type_to_str(ast_type_t type);
size_t get_node_size(ast_type_t type);

'''

################################################################
ast_header_ending = '''
#endif /* _AST_H_ */


'''

################################################################
ast_traverse_func = '''

/*
$rule */
void _traverse_$name($ast_name* node) {
    ENTER;
    RETURN();
}

'''

################################################################
ast_src_start = '''
/*
 * This is a generated file
 */
#include <stddef.h>
#include "ast.h"
#include "common.h"

'''

################################################################
ast_src_traverse = '''

/*
 * Main entry point for AST traverse
 */
void traverse_ast(ast_node_t* node) {
    ENTER;
    _traverse_$name(($ast_name*)node);
    RETURN();
}

ast_node_t* create_ast_node(ast_type_t type) {

    ast_node_t* node = _ALLOC(get_node_size(type));
    node->type = type;

    return node;
}

const char* node_type_to_str(ast_type_t type) {
    return
'''

################################################################
ast_type_to_str = '''}

size_t get_node_size(ast_type_t type) {
    size_t size =
'''

################################################################
ast_node_size = '''

    return size;
}

'''

################################################################
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

def make_rule(item):
    s = " *  "+item['name']+"\n"
    for x in item['body']:
        s += " *      "+x+"\n"

    return s

def mk_dirs():
    if(not os.path.isdir("./src")):
        os.mkdir("./src")

    if(not os.path.isdir("./src/ast")):
        os.mkdir("./src/ast")

def mk_ast_header(grammar):
    with open(dest_dir+"ast.h", "w") as fp:
        fp.write(ast_header_header);

        count = 512;
        for x in grammar:
            fp.write("    AST_%s = %d,\n"%(x['name'].upper(), count))
            count += 1

        fp.write(ast_nodes)
        tmp = Template(ast_struct)
        for x in grammar:
            fp.write(tmp.substitute(
                {'rule': make_rule(x),
                 'local_name': "_ast_"+x['name']+"_t",
                 'public_name': "ast_"+x['name']+"_t"}))

        fp.write(ast_header_protos)
        for x in grammar:
            fp.write("void _traverse_%s(ast_%s_t* node);\n"%(x['name'], x['name']))

        fp.write(ast_header_ending)

def mk_ast_source(grammar):
    with open(dest_dir+"ast.c", "w") as fp:
        fp.write(ast_src_start)
        tmp = Template(ast_traverse_func)
        for x in grammar:
            fp.write(tmp.substitute({
                'rule': make_rule(x), 'name': x['name'], 'ast_name': "ast_"+x['name']+"_t" }))

        tmp = Template(ast_src_traverse)
        fp.write(tmp.substitute(
                {'name': grammar[0]['name'],
                 'ast_name': "ast_"+grammar[0]['name']+"_t"}))
        for x in grammar:
            fp.write("    (type == AST_%s)? \"ast_%s_t\":\n"%(x['name'].upper(), x['name']))
        fp.write("    \"UNKNOWN\";\n")
        fp.write(ast_type_to_str)

        for x in grammar:
            fp.write("    (type == AST_%s)? sizeof(ast_%s_t):\n"%(x['name'].upper(), x['name']))
        fp.write("    (size_t)-1;\n")
        fp.write(ast_node_size);

g = get_grammar("simple.txt")
mk_dirs()
mk_ast_header(g)
mk_ast_source(g)
