
#include <stdio.h>

#include "common.h"
#include "fileio.h"
#include "parser.h"
#include "trace.h"

/**
 * @brief Create the command line data structures and parse the command line.
 * 
 * @param argc 
 * @param argv 
 * @param env 
 */
static void cmdline(int argc, char** argv, char** env) {

    init_cmdline("Simple", "Simple", "0.0.1");

    add_cmdline('p', "path", "path", "Add one or more items to the file search path", NULL, NULL, CMD_STR|CMD_ARGS|CMD_LIST);
    add_cmdline('t', "trace", "trace", "Trace an object (parser:scanner:AST:symbols)", NULL, NULL, CMD_STR|CMD_ARGS|CMD_LIST);
    add_cmdline('v', "verbosity", "verbosity", "Display debugging information", "50", NULL, CMD_NUM|CMD_ARGS);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    add_cmdline(0, NULL, NULL, NULL, NULL, NULL, CMD_DIV);
    add_cmdline(0, NULL, "files", "File name to input", NULL, NULL, CMD_REQD | CMD_ANON);
    parse_cmdline(argc, argv, env);

    string_t* str = get_cmd_opt("verbosity");
    push_verbosity(strtol(raw_string(str), NULL, 10));
    
    int mark = 0;
    for(string_t* str = iterate_cmd_opt("path", &mark); str != NULL; str = iterate_cmd_opt("path", &mark))
        add_dir_to_search(str);

}

/**
 * @brief Global main()
 * 
 * @param argc 
 * @param argv 
 * @param env 
 * @return int 
 */
int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);
    
    if(in_cmd_list("trace", "parser"))
        push_verbosity(100);
    else
        push_verbosity(0);
    parser_context_t* ctx = parse();
    pop_verbosity();

    if(in_cmd_list("trace", "AST"))
        push_verbosity(100);
    else
        push_verbosity(0);
    if(ctx->errors == 0) 
        traverse_ast(ctx->tree);
    pop_verbosity();

    if(peek_verbosity() > 1) 
        printf("errors %d: warnings %d\n", ctx->errors, ctx->warnings);
    return ctx->errors;
}
