
#include "common.h"
#include "scanner.h"
#include "fileio.h"

void cmdline(int argc, char** argv, char** env) {

    init_cmdline("scanner test", "scanner test", "0.0.1");

    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    add_cmdline(0, NULL, NULL, NULL, NULL, NULL, CMD_DIV);
    add_cmdline(0, NULL, "files", "File name to input", NULL, NULL, CMD_REQD | CMD_ANON);
    parse_cmdline(argc, argv, env);
}

/*
*/
int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

    open_file(get_cmd_opt("files"));
    create_scanner();

    token_t* tok;
    do {
        tok = scan_token();
        print_token(tok);
    } while(tok->type != TOK_END_OF_FILE);

    close_file();
    return 0;
}
