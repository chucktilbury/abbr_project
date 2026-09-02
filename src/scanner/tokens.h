#ifndef _TOKENS_H_
#define _TOKENS_H_

#include "common.h"

typedef enum {
    TOK_END_OF_FILE,
    TOK_END_OF_INPUT,
    // generated tokens
    TOK_IDENTIFIER,
    TOK_LITERAL_DSTR,
    TOK_LITERAL_SSTR,
    TOK_LITERAL_INT,
    TOK_LITERAL_UNS,
    TOK_LITERAL_FLOAT,
    // markers / operators
    TOK_LITERAL_TRUE,   // "true"
    TOK_LITERAL_FALSE,  // "false"
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LSQUARE,
    TOK_RSQUARE,
    TOK_LCURLY,
    TOK_RCURLY,
    TOK_LPOINTY,    // "<" AKA TOK_LT
    TOK_RPOINTY,    // ">" AKA TOK_GT
    TOK_COMMA,
    TOK_AMPER,      // "&"
    TOK_PIPE,       // "|"
    TOK_BANG,       // "!"
    TOK_CARAT,      // "^" AKA TOK_POW
    TOK_PERCENT,    // "%" AKA TOK_MOD
    TOK_DOT,
    TOK_COLON,
    // arith operators
    TOK_DIV,
    TOK_MUL,
    TOK_MOD,        // "%" AKA TOK_PERCENT
    TOK_MINUS,
    TOK_UNARY_MINUS,// assigned by expression parser
    TOK_UNARY_PLUS, // assigned by expression parser
    TOK_ADD,
    TOK_ASSIGN,     // "="
    TOK_POW,        // "^" AKA TOK_CARAT
    // logic operators
    TOK_EQU,        // "=="
    TOK_NEQ,        // "!="
    TOK_LT,         // "<" AKA TOK_LPOINTY
    TOK_GT,         // ">" AKA TOK_RPOINTY
    TOK_GTE,        // ">="
    TOK_LTE,        // "<="
    TOK_AND,        // "and" | "&"
    TOK_OR,         // "or" | "|"
    TOK_NOT,        // "not" | "!" always unary
    TOK_ADD_ASSIGN, // "+="
    TOK_SUB_ASSIGN, // "-="
    TOK_MUL_ASSIGN, // "*="
    TOK_DIV_ASSIGN, // "/="
    // key words
    TOK_NAMESPACE,  // "namespace"
    TOK_INCLUDE,    // "include"
    TOK_IMPORT,     // "import"
    TOK_AS,         // "as"
    TOK_CLASS,      // "class"
    TOK_PUBLIC,     // "public"
    TOK_PRIVATE,    // "private"
    TOK_PROTECTED,  // "protected"
    TOK_START,      // "start"
    TOK_CREATE,     // "create"
    TOK_DESTROY,    // "destroy"
    TOK_IF,         // "if"
    TOK_ELSE,       // "else"
    TOK_FOR,        // "for"
    TOK_WHILE,      // "while"
    TOK_DO,         // "do"
    TOK_BREAK,      // "break"
    TOK_CONTINUE,   // "continue"
    TOK_YIELD,      // "yield"
    TOK_TRY,        // "try"
    TOK_EXCEPT,     // "except"
    TOK_RAISE,      // "raise"
    TOK_RETURN,     // "return"
    // native type names
    TOK_INTEGER,    // "integer" | "int"
    TOK_UNSIGNED,   // "unsigned"
    TOK_FLOAT,      // "float"
    TOK_STRING,     // "string"
    TOK_DICT,       // "dictionary" | "dict" | "map"
    TOK_ARRAY,      // "array" | "list"
    TOK_BOOL,       // "boolean" | "bool"
    TOK_NOTHING,    // "nothing" | "noth"
    TOK_FINALLY,    // "finally"
    TOK_EXIT,       // "exit"
} token_type_t;

typedef struct _token_t {
    string_t* text;
    token_type_t type;
    string_t* fname;
    int line_no;
    int col_no;
} token_t;

token_t* create_token(string_t* text, token_type_t type);
token_t* create_token_str(const char* text, token_type_t type);
token_t* create_token_char(const int text, token_type_t type);
void destroy_token(token_t* tok);
const char* token_type_to_str(token_t* tok);
void print_token(token_t* tok);

#endif /* _TOKENS_H_ */
