
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "scanner.h"
#include "token_queue.h"
#include "fileio.h"

typedef struct _keyword_t {
    token_type_t type;
    const char* str;
} keyword_t;

static keyword_t key_words[] = {
    {TOK_LITERAL_TRUE,  "true"},
    {TOK_LITERAL_FALSE, "false"},
    {TOK_NAMESPACE, "namespace"},
    {TOK_INCLUDE,   "include"},
    {TOK_IMPORT,    "import"},
    {TOK_AS,        "as"},
    {TOK_CLASS,     "class"},
    {TOK_PUBLIC,    "public"},
    {TOK_PRIVATE,   "private"},
    {TOK_PROTECTED, "protected"},
    {TOK_START,     "start"},
    {TOK_CREATE,    "create"},
    {TOK_DESTROY,   "destroy"},
    {TOK_IF,        "if"},
    {TOK_ELSE,      "else"},
    {TOK_FOR,       "for"},
    {TOK_WHILE,     "while"},
    {TOK_DO,        "do"},
    {TOK_BREAK,     "break"},
    {TOK_CONTINUE,  "continue"},
    {TOK_YIELD,     "yield"},
    {TOK_TRY,       "try"},
    {TOK_EXCEPT,    "except"},
    {TOK_RAISE,     "raise"},
    {TOK_RETURN,    "return"},
    {TOK_INTEGER,   "integer"},
    {TOK_INTEGER,   "int"},
    {TOK_UNSIGNED,  "unsigned"},
    {TOK_FLOAT,     "float"},
    {TOK_STRING,    "string"},
    {TOK_DICT,      "dictionary"},
    {TOK_DICT,      "dict"},
    {TOK_DICT,      "map"},
    {TOK_ARRAY,     "array"},
    {TOK_ARRAY,     "list"},
    {TOK_BOOL,      "boolean"},
    {TOK_BOOL,      "bool"},
    {TOK_NOTHING,   "nothing"},
    {TOK_NOTHING,   "noth"},
    {TOK_FINALLY,   "finally"},
    {TOK_EXIT,      "exit"},
    {TOK_INLINE,    "inline"},
    {-1, NULL}
};

typedef struct _scanner_t {
    hash_table_t* keywords;
    int errors;
    int warnings;
} scanner_t;

static scanner_t* scanner = NULL;

static void consume_space(void) {

    int finished = 0;

    while(!finished) {
        int ch = get_char();
        if(!isspace(ch) || ch == EOF)
            finished = true;
        else
            consume_char();
    }
}

static void consume_single_line_comment(void) {

    int finished = 0;

    while(!finished) {
        int ch = consume_char();
        if(ch == '\n') {
            consume_char();
            finished = true;
        }
        else if(ch == EOF) {
            scanner_fatal("unexpected end of file in a comment");
        }
    }
}

static void consume_multi_line_comment(void) {

    int finished = 0;

    while(!finished) {
        int ch = consume_char();
        if(ch == '*') {
            ch = consume_char();
            if(ch == '/') {
                consume_char();
                finished = true;
            }
        }
        else if(ch == EOF) {
            scanner_fatal("unexpected end of file in a comment");
        }
    }
}

static token_t* read_operator(string_t* text) {

    int ch = text->buffer[0]; // get_char(); // = consume_char();
    token_t* tok = NULL;

    switch(ch) {
        case '!':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("!=", TOK_NEQ);
            }
            else {
                tok = create_token_str("!", TOK_NOT);
            }
            break;
        case '*':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("*=", TOK_MUL_ASSIGN);
            }
            else {
                tok = create_token_str("*", TOK_MUL);
            }
            break;
        case '-':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("-=", TOK_SUB_ASSIGN);
            }
            else {
                tok = create_token_str("-", TOK_MINUS);
            }
            break;
        case '+':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("+=", TOK_ADD_ASSIGN);
            }
            else {
                tok = create_token_str("+", TOK_ADD);

            }
            break;
        case '=':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("==", TOK_EQU);
            }
            else {
                tok = create_token_str("=", TOK_ASSIGN);
            }
            break;
        case '/':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("/=", TOK_DIV_ASSIGN);
            }
            else {
                tok = create_token_str("/", TOK_DIV);
            }
            break;
        case '<':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str("<=", TOK_LTE);
            }
            else {
                tok = create_token_str("<", TOK_LT);
            }
            break;
        case '>':
            ch = get_char(); //consume_char();
            if(ch == '=') {
                consume_char();
                tok = create_token_str(">=", TOK_GTE);
            }
            else {
                tok = create_token_str(">", TOK_GT);
            }
            break;

        case '%':
            tok = create_token_char(ch, TOK_MOD);
            break;
        case '^':
            tok = create_token_char(ch, TOK_POW);
            break;
        case '(':
            tok = create_token_char(ch, TOK_LPAREN);
            break;
        case ')':
            tok = create_token_char(ch, TOK_RPAREN);
            break;
        case '[':
            tok = create_token_char(ch, TOK_LSQUARE);
            break;
        case ']':
            tok = create_token_char(ch, TOK_RSQUARE);
            break;
        case '{':
            tok = create_token_char(ch, TOK_LCURLY);
            break;
        case '}':
            tok = create_token_char(ch, TOK_RCURLY);
            break;
        case ':':
            tok = create_token_char(ch, TOK_COLON);
            break;
        case ',':
            tok = create_token_char(ch, TOK_COMMA);
            break;
        case '.':
            tok = create_token_char(ch, TOK_DOT);
            break;
        default:
            scanner_warning("unexpected character: '0x%02X' ignored", ch);
    }

    return tok;
}

static token_t* get_mantissa(string_t* text) {

    int finished = 0;
    token_t* tok = NULL;

    int ch = get_char();
    if(ch == '-' || ch == '+') {
        append_string_char(text, ch);
        ch = consume_char();
    }

    if(isdigit(ch)) {
        while(!finished) {
            if(isdigit(ch)) {
                append_string_char(text, ch);
                ch = consume_char();
            }
            else
                finished = true;
        }
        tok = create_token(text, TOK_LITERAL_FLOAT);
    }
    else
        scanner_error("malformed literal float");

    return tok;
}

token_t* get_fractional_part(string_t* text) {

    int finished = 0;
    token_t* tok = NULL;

    int ch = get_char();
    while(!finished) {
        if(isdigit(ch)) {
            append_string_char(text, ch);
            ch = consume_char();
        }
        else
            finished = true;
    }

    // at least "0."
    if(text->len > 2) {
        if(ch == 'e' || ch == 'E') {
            append_string_char(text, ch);
            consume_char();
            return get_mantissa(text);
        }
        else {
            tok = create_token(text, TOK_LITERAL_FLOAT);
        }
    }
    else
        scanner_error("malformed literal float");

    return tok;
}

static token_t* get_hex_number(string_t* text) {

    int finished = 0;
    token_t* tok = NULL;

    int ch = get_char();
    while(!finished) {
        if(isxdigit(ch)) {
            append_string_char(text, ch);
            ch = consume_char();
        }
        else
            finished = true;
    }

    if(text->len > 2)
        tok = create_token(text, TOK_LITERAL_UNS);
    else
        scanner_error("invalid hex number format");

    return tok;
}

static token_t* float_or_unsigned(string_t* text) {

    token_t* tok = NULL;

    int ch = get_char();
    if(ch == '.') {
        append_string_char(text, ch);
        consume_char();
        tok = get_fractional_part(text);
    }
    else if(ch == 'x' || ch == 'X') {
        append_string_char(text, ch);
        consume_char();
        tok = get_hex_number(text);
    }
    else
        tok = create_token(text, TOK_LITERAL_INT);

    return tok;
}

static token_t* read_number(void) {

    string_t* text = create_string(NULL);
    token_t* tok = NULL;

    int ch = get_char();
    if(ch == '0') {
        append_string_char(text, ch);
        consume_char();
        tok = float_or_unsigned(text);
    }
    else {
        int finished = 0;
        while(!finished) {
            append_string_char(text, ch);
            ch = consume_char();
            if(!isdigit(ch))
                finished++;
        }

        if(ch == '.') {
            append_string_char(text, ch);
            consume_char();
            tok = get_fractional_part(text);
        }
        else
            tok = create_token(text, TOK_LITERAL_INT);
    }

    return tok;
}

static void capture_inline_text(token_t* tok) {

    clear_string(tok->text);
    int finished = 0;
    int count = 0;

    consume_space();

    int ch = get_char();
    if(ch != '{') {
        scanner_error("expected a '{' but got '%c'", ch);
        return;
    }

    while(!finished) {
        if(ch == '{')
            count++;
        else if(ch == '}')
            count--;

        append_string_char(tok->text, ch);
        consume_char();
        ch = get_char();

        if(count == 0)
            finished = 1;
    }
}

static token_t* read_symbol(void) {

    int finished = 0;
    string_t* text = create_string(NULL);
    token_t* tok = NULL;

    while(!finished) {
        int ch = get_char();
        if(isalpha(ch) || ch == '_') {
            consume_char();
            append_string_char(text, ch);
        }
        else
            finished = true;
    }

    // should be at least one....
    if(text->len > 0) {
        string_t* tmp = downcase_string(text);
        keyword_t* kw = find_hashtable(scanner->keywords, raw_string(tmp));
        if(kw != NULL)
            tok = create_token(tmp, kw->type);
        else
            tok = create_token(text, TOK_IDENTIFIER);
    }
    else
        scanner_fatal("generic fatal error");

    if(tok->type == TOK_INLINE)
        capture_inline_text(tok);

    return tok;
}

static token_t* read_dstr(void) {

    consume_char(); // consume the leading '\"'
    int finished = 0;
    token_t* tok = NULL;
    string_t* text = create_string(NULL);

    while(!finished) {
        int ch = get_char();
        if(ch == '\\') {
            int tmp = consume_char();
            switch(tmp) {
                case '\"': append_string_char(text, '\"'); break;
                case '\'': append_string_char(text, '\''); break;
                case '?': append_string_char(text, '\?'); break;
                case '\\': append_string_char(text, '\\'); break;
                case 'a': append_string_char(text, '\a'); break;
                case 'f': append_string_char(text, '\f'); break;
                case 'n': append_string_char(text, '\n'); break;
                case 'r': append_string_char(text, '\r'); break;
                case 't': append_string_char(text, '\t'); break;
                case 'v': append_string_char(text, '\v'); break;
                case 'b': append_string_char(text, '\b'); break;
                case 'e': append_string_char(text, '\x1b'); break;
                case 'x':
                case 'X': {
                    string_t* s = create_string(NULL);
                    for(int t2 = consume_char(), i = 0; i < 2; i++, t2 = consume_char())
                        append_string_char(s, t2);
                    int t = (unsigned char)strtol(raw_string(s), NULL, 16);
                    append_string_char(text, t);
                    destroy_string(s);
                } break;
                default:
                    append_string_char(text, '\\');
                    append_string_char(text, ch);
                    break;
            }
            consume_char();
        }
        else if(ch == '\"') {
            consume_char();
            tok = create_token(text, TOK_LITERAL_DSTR);
            finished++;
        }
        else if(ch == '\n') {
            scanner_error("unexpected newline in quoted string");
            finished++;
        }
        else if(ch == EOF) {
            scanner_fatal("unexpected end of file in quoted string"); // does not return
        }
        else {
            append_string_char(text, ch);
            consume_char();
        }
    }

    return tok;
}

static token_t* read_sstr(void) {

    consume_char(); // consume the leading '\''
    int finished = 0;
    token_t* tok = NULL;
    string_t* text = create_string(NULL);

    while(!finished) {
        int ch = get_char();
        if(ch == '\'') {
            consume_char();
            tok = create_token(text, TOK_LITERAL_SSTR);
            finished = true;
        }
        else if(ch == '\n') {
            scanner_error("unexpected newline in quoted string");
            finished = true;
        }
        else if(ch == EOF) {
            scanner_fatal("unexpected end of file in quoted string");
        }
        else {
            append_string_char(text, ch);
            consume_char();
        }
    }

    return tok;
}

token_t* scan_token(void) {

    int finished = 0;
    token_t* tok;
    string_t* text = create_string(NULL);

    while(!finished) {
        int ch = get_char();
        if(ch == '/') {
            ch = consume_char();
            if(ch == '/')
                consume_single_line_comment();
            else if(ch == '*')
                consume_multi_line_comment();
            else {
                append_string_char(text, '/');
                tok = read_operator(text);
                finished++;
            }
        }
        else if(ch == ';' || ch == '#') {
            consume_single_line_comment();
        }
        else if(isspace(ch)) {
            consume_char();
        }
        else if(ch == '\"') {
            tok = read_dstr();
            finished++;
        }
        else if(ch == '\'') {
            tok = read_sstr();
            finished++;
        }
        else if(ispunct(ch)) {
            append_string_char(text, ch);
            consume_char();
            tok = read_operator(text);
            // might ignore an operator
            if(tok != NULL) {
                finished++;
            }
        }
        else if(isdigit(ch)) {
            tok = read_number();
            finished++;
        }
        else if(ch == '_' || isalpha(ch)) {
            tok = read_symbol();
            finished++;
        }
        else if(ch == EOF) {
            tok = create_token(create_string(NULL), TOK_END_OF_FILE);
            finished++;
        }

    }

    return tok;
}

void create_scanner(void) {

    scanner_t* ptr = _ALLOC_TYPE(scanner_t);
    hash_table_t* table = create_hashtable();

    for(int i = 0; key_words[i].str != NULL; i++)
        insert_hashtable(table, key_words[i].str, (void*)&key_words[i]);

    ptr->errors = 0;
    ptr->warnings = 0;
    ptr->keywords = table;

    scanner = ptr;
}

void destroy_scanner(void) {

    if(scanner != NULL) {
        destroy_hashtable(scanner->keywords);
        _FREE(scanner);
    }
}

void scanner_error(const char* fmt, ...) {

    fprintf(stderr, "scanner error: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    scanner->errors++;
}

void scanner_warning(const char* fmt, ...) {

    fprintf(stderr, "scanner warning: %s: %d: %d: ", raw_string(get_file_name()), get_line_no(), get_col_no());

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    scanner->warnings++;
}

void scanner_fatal(const char* fmt, ...) {

    fprintf(stderr, "fatal scanner error: ");

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    scanner->errors++;
    exit(1);
}

