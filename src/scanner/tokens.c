
#include "tokens.h"
#include "fileio.h"

token_t* create_token(string_t* text, token_type_t type) {
    token_t* ptr = _ALLOC_TYPE(token_t);
    ptr->text = copy_string(text);
    ptr->type = type;
    ptr->fname = copy_string(get_file_name());
    ptr->line_no = get_line_no();
    ptr->col_no = get_col_no();

    return ptr;
}

token_t* create_token_str(const char* text, token_type_t type) {
    return create_token(create_string(text), type);
}

token_t* create_token_char(const int text, token_type_t type) {
    string_t* str = create_string(NULL);
    append_string_char(str, text);
    return create_token(str, type);
}

void destroy_token(token_t* tok) {

    if(tok) {
        destroy_string(tok->text);
        destroy_string(tok->fname);
        _FREE(tok);
    }
}

const char* token_type_to_str(token_type_t type) {
    return
    (type == TOK_END_OF_FILE)?    "end of file" :
    (type == TOK_END_OF_INPUT)?   "end of input" :
    (type == TOK_IDENTIFIER)?     "identifier" :
    (type == TOK_LITERAL_DSTR)?   "literal string" :
    (type == TOK_LITERAL_SSTR)?   "literal string" :
    (type == TOK_LITERAL_INT)?    "literal integer" :
    (type == TOK_LITERAL_UNS)?    "literal unsigned" :
    (type == TOK_LITERAL_FLOAT)?  "literal float" :
    (type == TOK_LITERAL_TRUE)?   "true" :
    (type == TOK_LITERAL_FALSE)?  "false" :
    (type == TOK_LPAREN)?     "(" :
    (type == TOK_RPAREN)?     ")" :
    (type == TOK_LSQUARE)?    "[" :
    (type == TOK_RSQUARE)?    "]" :
    (type == TOK_LCURLY)?     "{" :
    (type == TOK_RCURLY)?     "}" :
    (type == TOK_LPOINTY)?    "<" :
    (type == TOK_RPOINTY)?    ">" :
    (type == TOK_COMMA)?      "," :
    (type == TOK_AMPER)?      "&" :
    (type == TOK_PIPE)?       "|" :
    (type == TOK_BANG)?       "!" :
    (type == TOK_CARAT)?      "^" :
    (type == TOK_PERCENT)?    "%" :
    (type == TOK_DOT)?        "." :
    (type == TOK_COLON)?      ":" :
    (type == TOK_DIV)?        "/" :
    (type == TOK_MUL)?        "*" :
    (type == TOK_MOD)?        "%" :
    (type == TOK_MINUS)?      "-" :
    (type == TOK_ADD)?        "+" :
    (type == TOK_ASSIGN)?     "=" :
    (type == TOK_POW)?        "^" :
    (type == TOK_EQU)?        "==" :
    (type == TOK_NEQ)?        "!=" :
    (type == TOK_LT)?         "<" :
    (type == TOK_GT)?         ">" :
    (type == TOK_GTE)?        ">=" :
    (type == TOK_LTE)?        "<=" :
    (type == TOK_AND)?        "and" :
    (type == TOK_OR)?         "or" :
    (type == TOK_NOT)?        "not" :
    (type == TOK_ADD_ASSIGN)? "+=" :
    (type == TOK_SUB_ASSIGN)? "-=" :
    (type == TOK_MUL_ASSIGN)? "*=" :
    (type == TOK_DIV_ASSIGN)? "/=" :
    (type == TOK_NAMESPACE)?  "namespace" :
    (type == TOK_INCLUDE)?    "include" :
    (type == TOK_IMPORT)?     "import" :
    (type == TOK_AS)?         "as" :
    (type == TOK_CLASS)?      "class" :
    (type == TOK_PUBLIC)?     "public" :
    (type == TOK_PRIVATE)?    "private" :
    (type == TOK_PROTECTED)?  "protected" :
    (type == TOK_START)?      "start" :
    (type == TOK_CREATE)?     "create" :
    (type == TOK_DESTROY)?    "destroy" :
    (type == TOK_IF)?         "if" :
    (type == TOK_ELSE)?       "else" :
    (type == TOK_FOR)?        "for" :
    (type == TOK_WHILE)?      "while" :
    (type == TOK_DO)?         "do" :
    (type == TOK_BREAK)?      "break" :
    (type == TOK_CONTINUE)?   "continue" :
    (type == TOK_YIELD)?      "yield" :
    (type == TOK_TRY)?        "try" :
    (type == TOK_EXCEPT)?     "except" :
    (type == TOK_RAISE)?      "raise" :
    (type == TOK_RETURN)?     "return" :
    (type == TOK_INTEGER)?    "integer" :
    (type == TOK_UNSIGNED)?   "unsigned" :
    (type == TOK_FLOAT)?      "float" :
    (type == TOK_STRING)?     "string" :
    (type == TOK_DICT)?       "dictionary" :
    (type == TOK_ARRAY)?      "array" :
    (type == TOK_BOOL)?       "boolean" :
    (type == TOK_NOTHING)?    "nothing" :
    (type == TOK_EXIT)?        "exit" :
    (type == TOK_INLINE)?      "inline" :
    (type == TOK_UNARY_PLUS)?  "+" :
    (type == TOK_UNARY_MINUS)? "-" :
    (type == TOK_FINALLY)?    "finally" : "UNKNOWN";
}

void print_token(token_t* tok) {

    if(tok != NULL) {
    printf("tok text \"%s\": type \"%s\" ", raw_string(tok->text), token_type_to_str(tok->type));
        printf("file \"%s\": line %d: column %d\n", raw_string(tok->fname), tok->line_no, tok->col_no);
    }
    else
        printf("NULL TOKEN\n");
}

