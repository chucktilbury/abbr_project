
#include "common.h"
#include "token_queue.h"

void cmdline(int argc, char** argv, char** env) {

    init_cmdline("scanner test", "scanner test", "0.0.1");

    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    add_cmdline(0, NULL, NULL, NULL, NULL, NULL, CMD_DIV);
    add_cmdline(0, NULL, "files", "File name to input", NULL, NULL, CMD_REQD | CMD_ANON);
    parse_cmdline(argc, argv, env);
}

/*
    This simulates trying 3 rules where the last one succeeds and then read
    a few more tokens.
 */
int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

    create_token_queue(get_cmd_opt("files"));

    token_t* tok = get_token();

    printf("-------- get first item:\n");
    print_token(tok);

    // first non-terminal
    printf("\n-------- first try read 5 more items into the queue --------\n");
    mark_token_queue();
    for(int i = 0; i < 5; i++) {
        print_token(tok);
        tok = consume_token();
    }
    print_token_queue();

    // a second non-terminal
    printf("\n-------- second non-terminal read 8 more items into the queue --------\n");
    mark_token_queue();
    for(int i = 0; i < 8; i++) {
        print_token(tok);
        tok = consume_token();
    }
    print_token_queue();

    printf("\n-------- second non-terminal fails --------\n");
    reset_token_queue();
    print_token_queue();
    printf("\n-------- first non-terminal fails --------\n");
    reset_token_queue();
    print_token_queue();

    printf("\n-------- second try read 5 items --------\n");
    mark_token_queue();
    for(int i = 0; i < 5; i++) {
        print_token(tok);
        tok = consume_token();
    }
    print_token_queue();

    printf("\n-------- accept the rule of 5 items --------\n");
    flush_token_queue();
    print_token_queue();

    printf("\n-------- mark and read 5 more items --------\n");
    mark_token_queue();
    for(int i = 0; i < 7; i++) {
        print_token(tok);
        tok = consume_token();
    }
    print_token_queue();

    return 0;
}

/*
    printf("-------- read first item:\n");
    print_token(get_token());

    printf("\n-------- read 5 more items into the queue --------\n");
    for(int i = 0; i < 5; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- drop a mark and read 5 more items into the queue --------\n");
    mark_token_queue();
    for(int i = 0; i < 5; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- reset the queue and read 7 items --------\n");
    reset_token_queue();
    for(int i = 0; i < 7; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- the token queue marker stack is empty --------\n");
    flush_token_queue();
    printf("-------- push a new item on it at the end of the queue --------\n");
    mark_token_queue();
    printf("\n-------- read 5 more items into the queue --------\n");
    for(int i = 0; i < 5; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- delete the previous 17 items --------");
    accept_token_queue();
    print_token_queue();

    printf("\n-------- mark the queue and read 5 more items --------\n");
    mark_token_queue();
    for(int i = 0; i < 5; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- mark the queue and read 5 more items --------\n");
    mark_token_queue();
    for(int i = 0; i < 5; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();


    printf("\n-------- read 8 more items --------\n");
    for(int i = 0; i < 8; i++) {
        tok = consume_token();
        print_token(tok);
    }
    print_token_queue();

    printf("\n-------- reset the queue and accept 5 items --------\n");
    reset_token_queue();
    printf("-------- read current item:\n");
    print_token(get_token());
    accept_token_queue();
    print_token_queue();

    return 0;
}

 */