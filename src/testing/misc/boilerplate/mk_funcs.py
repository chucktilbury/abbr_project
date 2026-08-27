#!/usr/bin/python3
import sys, os
from string import Template
import re

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

###########################################################
ast_header_template = '''
/*

$rule
 */
#ifndef $guard
#define $guard

#include "_ast_node.h"
#include "tokens.h"
#include "logger.h"

class $name: public _ast_node {

    public:
    $name(Token* tok):
        _ast_node(tok, _ast_node::$ast_name) {}

    virtual void before() {}
    virtual void after() {}

    void traverse() {
        ENTER;
        before();
        // logger.fatal(std::format("internal error in {}", __PRETTY_FUNCTION__));
        after();
        RETURN();
    }

    // parser elements here

};

#endif /* $guard */

'''

###########################################################
ast_node_begin = '''
#ifndef __AST_NODE_H_
#define __AST_NODE_H_

#include <string>
#include "tokens.h"

class _ast_node {
    public:
    enum {
'''

###########################################################
ast_node_end = '''
    };

    _ast_node(Token* tok, int type)
            : token(tok)
            , node_type(type) {}

    int get_line_no() {
        return token->line_no;
    }

    int get_col_no() {
        return token->col_no;
    }

    const std::string& get_file_name() {
        return token->fname;
    }

    int type() {
        return node_type;
    }

    const char* to_string();

    private:
    Token* token;
    int node_type;
};

'''

###########################################################
ast_source = '''

#include "_ast_node.h"

const char* _ast_node::to_string() {
    return
'''

###########################################################
parser_file_source = '''

#include <format>
#include "_parser.h"
#include "logger.h"

/*

$rule
*/
$retv* Parser::$name() {
    ENTER;
    $retv* node = nullptr;
    // define node attribs

    bool finished = false;
    int state = Parser::START_STATE;
    tqueue.mark();

    while(!finished) {
        switch(state) {
            case Parser::START_STATE: {
                STATE;
            } break;

            case Parser::RETURN_MATCH: {
                STATE;
                node = new $retv(TOKEN);
                // set node attribs
                tqueue.flush();
                finished = true;
            } break;

            case Parser::RETURN_NO_MATCH: {
                STATE;
                tqueue.reset();
                finished = true;
            } break;

            case Parser::RETURN_ERROR: {
                STATE;
                finished = error_recovery();
            } break;

            default:
                STATE;
                _fatal(std::format("unknown state in {}(): {}", __PRETTY_FUNCTION__, state));
        }
    }

    RETURN(node);
}

'''
###########################################################
parser_header_begin = '''
#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include "token_queue.h"
#include "_ast_node.h"

class Parser {

    public:
    enum {
        START_STATE = 100,
        REPEAT_STATE = 200,
        RETURN_MATCH = 300,
        RETURN_NO_MATCH = 400,
        RETURN_ERROR = 500,

        ZOO_STATE_0 = 600,
        ZOO_REPEAT_STATE_0 = 610,
        ZOO_STATE_1 = 601,
        ZOO_REPEAT_STATE_1 = 611,
        ZOO_STATE_2 = 602,
        ZOO_REPEAT_STATE_2 = 612,
        ZOO_STATE_3 = 603,
        ZOO_REPEAT_STATE_3 = 613,
        ZOO_STATE_4 = 604,
        ZOO_REPEAT_STATE_4 = 614,
        ZOO_STATE_5 = 605,
        ZOO_REPEAT_STATE_5 = 615,
        ZOO_STATE_6 = 606,
        ZOO_REPEAT_STATE_6 = 616,
        ZOO_STATE_7 = 607,
        ZOO_REPEAT_STATE_7 = 617,
        ZOO_STATE_8 = 608,
        ZOO_REPEAT_STATE_8 = 618,
        ZOO_STATE_9 = 609,
        ZOO_REPEAT_STATE_9 = 619,

        ZOM_STATE_0 = 700,
        ZOM_REPEAT_STATE_0 = 710,
        ZOM_STATE_1 = 701,
        ZOM_REPEAT_STATE_1 = 711,
        ZOM_STATE_2 = 702,
        ZOM_REPEAT_STATE_2 = 712,
        ZOM_STATE_3 = 703,
        ZOM_REPEAT_STATE_3 = 713,
        ZOM_STATE_4 = 704,
        ZOM_REPEAT_STATE_4 = 714,
        ZOM_STATE_5 = 705,
        ZOM_REPEAT_STATE_5 = 715,
        ZOM_STATE_6 = 706,
        ZOM_REPEAT_STATE_6 = 716,
        ZOM_STATE_7 = 707,
        ZOM_REPEAT_STATE_7 = 717,
        ZOM_STATE_8 = 708,
        ZOM_REPEAT_STATE_8 = 718,
        ZOM_STATE_9 = 709,
        ZOM_REPEAT_STATE_9 = 719,

        OOM_STATE_0 = 800,
        OOM_REPEAT_STATE_0 = 810,
        OOM_STATE_1 = 801,
        OOM_REPEAT_STATE_1 = 811,
        OOM_STATE_2 = 802,
        OOM_REPEAT_STATE_2 = 812,
        OOM_STATE_3 = 803,
        OOM_REPEAT_STATE_3 = 813,
        OOM_STATE_4 = 804,
        OOM_REPEAT_STATE_4 = 814,
        OOM_STATE_5 = 805,
        OOM_REPEAT_STATE_5 = 815,
        OOM_STATE_6 = 806,
        OOM_REPEAT_STATE_6 = 816,
        OOM_STATE_7 = 807,
        OOM_REPEAT_STATE_7 = 817,
        OOM_STATE_8 = 808,
        OOM_REPEAT_STATE_8 = 818,
        OOM_STATE_9 = 809,
        OOM_REPEAT_STATE_9 = 819,
    };

    Parser() {
        ENTER;
        tqueue = TokenQueue();
        errors = 0;
        warnings = 0;
        RETURN();
    }

    _ast_node* parse();
    int get_errors() {
        return errors;
    }
    int get_warnings() {
        return warnings;
    }

    void open_file(const std::string& fname) {
        tqueue.open_file(fname);
    }

    void close_file() {
        tqueue.close_file();
    }

    private:
    // member prototypes
'''
parser_header_end = '''

    bool error_recovery(_ast_node* node);
    bool error_recovery();

    void _error(std::string msg);
    void _warning(std::string msg);
    void _error(Token* tok, std::string msg);
    void _warning(Token* tok, std::string msg);
    void _fatal(std::string msg);
    const char* state_name(int state);

    TokenQueue tqueue;
    int errors;
    int warnings;
};

#define TOKEN tqueue.token()
#define TOKEN_STR TOKEN->get_text()
#define TOKEN_TYPE TOKEN->get_type()
#define ADVANCE tqueue.advance()
#define STATE do { \\
    if(logger.get_level() >= Logger::DEBUG) { \\
        logger.pad(); \\
        std::print(stdout, "STATE: {}: {}\\n", __PRETTY_FUNCTION__, state_name(state)); \\
    } \\
} while(false)

#endif /* _PARSER_H_ */

'''

###########################################################
parser_source = '''
#include <iostream>
#include "_parser.h"
#include "logger.h"

_ast_node* Parser::parse() {
    ENTER;
    // logger.push_level(Logger::WARNING);
    _ast_node* node = (_ast_node*)$first();
    // logger.pop_level();
    RETURN(node);
}

bool Parser::error_recovery(_ast_node* node) {
    ENTER;
    (void)node;
    RETURN(true);
}

bool Parser::error_recovery() {
    RETURN(true);
}


const char* Parser::state_name(int state) {
    return
        (state == START_STATE)? "start state" :
        (state == REPEAT_STATE)? "repeat state" :
        (state == RETURN_MATCH)? "return match" :
        (state == RETURN_NO_MATCH)? "return no match" :
        (state == RETURN_ERROR)? "return error" :

        (state == ZOO_STATE_0)? "zero or one state 0" :
        (state == ZOO_REPEAT_STATE_0)? "zero or one repeat state 0" :
        (state == ZOO_STATE_1)? "zero or one state 1" :
        (state == ZOO_REPEAT_STATE_1)? "zero or one repeat state 1" :
        (state == ZOO_STATE_2)? "zero or one state 2" :
        (state == ZOO_REPEAT_STATE_2)? "zero or one repeat state 2" :
        (state == ZOO_STATE_3)? "zero or one state 3" :
        (state == ZOO_REPEAT_STATE_3)? "zero or one repeat state 3" :
        (state == ZOO_STATE_4)? "zero or one state 4" :
        (state == ZOO_REPEAT_STATE_4)? "zero or one repeat state 4" :
        (state == ZOO_STATE_5)? "zero or one state 5" :
        (state == ZOO_REPEAT_STATE_5)? "zero or one repeat state 5" :
        (state == ZOO_STATE_6)? "zero or one state 6" :
        (state == ZOO_REPEAT_STATE_6)? "zero or one repeat state 6" :
        (state == ZOO_STATE_7)? "zero or one state 7" :
        (state == ZOO_REPEAT_STATE_7)? "zero or one repeat state 7" :
        (state == ZOO_STATE_8)? "zero or one state 8" :
        (state == ZOO_REPEAT_STATE_8)? "zero or one repeat state 8" :
        (state == ZOO_STATE_9)? "zero or one state 9" :
        (state == ZOO_REPEAT_STATE_9)? "zero or one repeat state 9" :

        (state == ZOM_STATE_0)? "zero or more state 0" :
        (state == ZOM_REPEAT_STATE_0)? "zero or more repeat state 0" :
        (state == ZOM_STATE_1)? "zero or more state 1" :
        (state == ZOM_REPEAT_STATE_1)? "zero or more repeat state 1" :
        (state == ZOM_STATE_2)? "zero or more state 2" :
        (state == ZOM_REPEAT_STATE_2)? "zero or more repeat state 2" :
        (state == ZOM_STATE_3)? "zero or more state 3" :
        (state == ZOM_REPEAT_STATE_3)? "zero or more repeat state 3" :
        (state == ZOM_STATE_4)? "zero or more state 4" :
        (state == ZOM_REPEAT_STATE_4)? "zero or more repeat state 4" :
        (state == ZOM_STATE_5)? "zero or more state 5" :
        (state == ZOM_REPEAT_STATE_5)? "zero or more repeat state 5" :
        (state == ZOM_STATE_6)? "zero or more state 6" :
        (state == ZOM_REPEAT_STATE_6)? "zero or more repeat state 6" :
        (state == ZOM_STATE_7)? "zero or more state 7" :
        (state == ZOM_REPEAT_STATE_7)? "zero or more repeat state 7" :
        (state == ZOM_STATE_8)? "zero or more state 8" :
        (state == ZOM_REPEAT_STATE_8)? "zero or more repeat state 8" :
        (state == ZOM_STATE_9)? "zero or more state 9" :
        (state == ZOM_REPEAT_STATE_9)? "zero or more repeat state 9" :

        (state == OOM_STATE_9)? "one or more state 9" :
        (state == OOM_REPEAT_STATE_9)? "one or more repeat state 9" :
        (state == OOM_STATE_0)? "one or more state 0" :
        (state == OOM_REPEAT_STATE_0)? "one or more repeat state 0" :
        (state == OOM_STATE_1)? "one or more state 1" :
        (state == OOM_REPEAT_STATE_1)? "one or more repeat state 1" :
        (state == OOM_STATE_2)? "one or more state 2" :
        (state == OOM_REPEAT_STATE_2)? "one or more repeat state 2" :
        (state == OOM_STATE_3)? "one or more state 3" :
        (state == OOM_REPEAT_STATE_3)? "one or more repeat state 3" :
        (state == OOM_STATE_4)? "one or more state 4" :
        (state == OOM_REPEAT_STATE_4)? "one or more repeat state 4" :
        (state == OOM_STATE_5)? "one or more state 5" :
        (state == OOM_REPEAT_STATE_5)? "one or more repeat state 5" :
        (state == OOM_STATE_6)? "one or more state 6" :
        (state == OOM_REPEAT_STATE_6)? "one or more repeat state 6" :
        (state == OOM_STATE_7)? "one or more state 7" :
        (state == OOM_REPEAT_STATE_7)? "one or more repeat state 7" :
        (state == OOM_STATE_8)? "one or more state 8" :
        (state == OOM_REPEAT_STATE_8)? "one or more repeat state 8" :
        "UNKNOWN";
}

void Parser::_error(std::string msg) {

    std::cerr << "syntax error: " << msg << std::endl;
    errors++;
}

void Parser::_warning(std::string msg) {

    std::cerr << "syntax warning: " << msg << std::endl;
    warnings++;
}

void Parser::_error(Token* tok, std::string msg) {

    std::cerr << tok->fname << ": "
         << tok->line_no << ": "
         << tok->col_no << ": "
         << "syntax error: " << msg << std::endl;
    errors++;
}

void Parser::_warning(Token* tok, std::string msg) {

    std::cerr << tok->fname << ": "
         << tok->line_no << ": "
         << tok->col_no << ": "
         << "syntax warning: " << msg << std::endl;
    warnings++;
}

void Parser::_fatal(std::string msg) {

    std::cerr << "fatal error: " << msg << std::endl;
    exit(1);
}

'''

###########################################################
def make_rule(item):
    s = "    "+item['name']+"\n"
    for x in item['body']:
        s += "        "+x+"\n"

    return s

def ast_header(item):
    tmp = Template(ast_header_template)
    return tmp.substitute(
        {'name':"_ast_"+item['name'],
        'ast_name':"AST_"+item['name'].upper(),
        'rule':make_rule(item),
        'guard':"__AST_"+item['name'].upper()+"_H_"})

def emit_ast_node(grammar):
    with open("./src/ast/_ast_node.h", "w") as fp:
        fp.write(ast_node_begin)
        for item in grammar:
            fp.write("        AST_"+item['name'].upper()+",\n")
        fp.write(ast_node_end)
        for item in grammar:
            fp.write("class _ast_"+item['name']+";\n")
        fp.write("\n")
        for item in grammar:
            fp.write("#include \"_ast_"+item['name']+".h\"\n")
        fp.write("\n\n#endif /* __AST_NODE_H_ */\n\n\n")

    with open("./src/ast/_ast_node.cpp", "w") as fp:
        fp.write(ast_source)
        for item in grammar:
            fp.write("        (node_type == AST_"+item['name'].upper()+")? \""+"_ast_"+item['name']+"\" :\n")
        fp.write("        \"UNKNOWN\";\n}\n\n")


def emit_ast(grammar):
    if(not os.path.isdir("./src")):
        os.mkdir("./src")

    if(not os.path.isdir("./src/ast")):
        os.mkdir("./src/ast")

    for item in grammar:
        with open("./src/ast/_ast_"+item['name']+".h", "w") as fp:
            fp.write(ast_header(item))

    emit_ast_node(grammar)


    with open("ast_file_list.txt", "w") as fp:
        for item in grammar:
            fp.write("_ast_"+item['name']+".cpp\n")


def mk_parser_src(item):
    tmp = Template(parser_file_source)
    return tmp.substitute(
            {'name':"_parse_"+item['name'],
             'retv':"_ast_"+item['name'],
             'rule':make_rule(item)})

def emit_parser(grammar):
    if(not os.path.isdir("./src")):
        os.mkdir("./src")

    if(not os.path.isdir("./src/parser")):
        os.mkdir("./src/parser")

    for item in grammar:
        with open("./src/parser/_parse_"+item['name']+".cpp", "w") as fp:
            fp.write(mk_parser_src(item))

    with open("./src/parser/_parser.h", "w") as fp:
        fp.write(parser_header_begin)
        for item in grammar:
            fp.write("    _ast_"+item['name']+"* "+"_parse_"+item['name']+"();\n")
        fp.write(parser_header_end)

    with open("./src/parser/_parser.cpp", "w") as fp:
        tmp = Template(parser_source)
        fp.write(tmp.substitute({'first':"_parse_"+grammar[0]['name'],
                                 'rule': make_rule(item)}))

    with open("parser_file_list.txt", "w") as fp:
        for item in grammar:
            fp.write("_parse_"+item['name']+".cpp\n")

g = get_grammar("simple.txt")
emit_ast(g)
emit_parser(g)
