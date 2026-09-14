
#include <stdio.h>

#include "common.h"
#include "fileio.h"
#include "parser.h"

void cmdline(int argc, char** argv, char** env) {

    init_cmdline("Simple", "Simple", "0.0.1");

    add_cmdline('v', "verbosity", "verbosity", "Display debugging information", "50", NULL, CMD_NUM|CMD_ARGS);
    add_cmdline('p', "path", "path", "Add one or more items to the file search path", "./", NULL, CMD_STR|CMD_ARGS|CMD_LIST);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    add_cmdline(0, NULL, NULL, NULL, NULL, NULL, CMD_DIV);
    add_cmdline(0, NULL, "files", "File name to input", NULL, NULL, CMD_REQD | CMD_ANON);
    parse_cmdline(argc, argv, env);

    string_t* str = get_cmd_opt("verbosity");
    verbosity = strtol(raw_string(str), NULL, 10);
    
}

/*
*/
int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);
    
    parser_context_t* ctx = parse();

    if(ctx->errors == 0) 
        traverse_ast(ctx->tree);



    close_file();
    return 0;
}
