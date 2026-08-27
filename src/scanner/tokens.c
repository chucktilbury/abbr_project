
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

const char* token_type_to_str(token_t* tok) {
    return
    (tok->type == TOK_END_OF_FILE)?    "end of file" :
    (tok->type == TOK_END_OF_INPUT)?   "end of input" :
    (tok->type == TOK_IDENTIFIER)?     "identifier" :
    (tok->type == TOK_LITERAL_DSTR)?   "literal string" :
    (tok->type == TOK_LITERAL_SSTR)?   "literal string" :
    (tok->type == TOK_LITERAL_INT)?    "literal integer" :
    (tok->type == TOK_LITERAL_UNS)?    "literal unsigned" :
    (tok->type == TOK_LITERAL_FLOAT)?  "literal float" :
    (tok->type == TOK_LITERAL_TRUE)?   "true" :
    (tok->type == TOK_LITERAL_FALSE)?  "false" :
    (tok->type == TOK_LPAREN)?     "(" :
    (tok->type == TOK_RPAREN)?     ")" :
    (tok->type == TOK_LSQUARE)?    "[" :
    (tok->type == TOK_RSQUARE)?    "]" :
    (tok->type == TOK_LCURLY)?     "{" :
    (tok->type == TOK_RCURLY)?     "}" :
    (tok->type == TOK_LPOINTY)?    "<" :
    (tok->type == TOK_RPOINTY)?    ">" :
    (tok->type == TOK_COMMA)?      "," :
    (tok->type == TOK_AMPER)?      "&" :
    (tok->type == TOK_PIPE)?       "|" :
    (tok->type == TOK_BANG)?       "!" :
    (tok->type == TOK_CARAT)?      "^" :
    (tok->type == TOK_PERCENT)?    "%" :
    (tok->type == TOK_DOT)?        "." :
    (tok->type == TOK_COLON)?      ":" :
    (tok->type == TOK_DIV)?        "/" :
    (tok->type == TOK_MUL)?        "*" :
    (tok->type == TOK_MOD)?        "%" :
    (tok->type == TOK_MINUS)?      "-" :
    (tok->type == TOK_ADD)?        "+" :
    (tok->type == TOK_ASSIGN)?     "=" :
    (tok->type == TOK_POW)?        "^" :
    (tok->type == TOK_EQU)?        "==" :
    (tok->type == TOK_NEQ)?        "!=" :
    (tok->type == TOK_LT)?         "<" :
    (tok->type == TOK_GT)?         ">" :
    (tok->type == TOK_GTE)?        ">=" :
    (tok->type == TOK_LTE)?        "<=" :
    (tok->type == TOK_AND)?        "and" :
    (tok->type == TOK_OR)?         "or" :
    (tok->type == TOK_NOT)?        "not" :
    (tok->type == TOK_ADD_ASSIGN)? "+=" :
    (tok->type == TOK_SUB_ASSIGN)? "-=" :
    (tok->type == TOK_MUL_ASSIGN)? "*=" :
    (tok->type == TOK_DIV_ASSIGN)? "/=" :
    (tok->type == TOK_NAMESPACE)?  "namespace" :
    (tok->type == TOK_INCLUDE)?    "include" :
    (tok->type == TOK_IMPORT)?     "import" :
    (tok->type == TOK_AS)?         "as" :
    (tok->type == TOK_CLASS)?      "class" :
    (tok->type == TOK_PUBLIC)?     "public" :
    (tok->type == TOK_PRIVATE)?    "private" :
    (tok->type == TOK_PROTECTED)?  "protected" :
    (tok->type == TOK_START)?      "start" :
    (tok->type == TOK_CREATE)?     "create" :
    (tok->type == TOK_DESTROY)?    "destroy" :
    (tok->type == TOK_IF)?         "if" :
    (tok->type == TOK_ELSE)?       "else" :
    (tok->type == TOK_FOR)?        "for" :
    (tok->type == TOK_WHILE)?      "while" :
    (tok->type == TOK_DO)?         "do" :
    (tok->type == TOK_BREAK)?      "break" :
    (tok->type == TOK_CONTINUE)?   "continue" :
    (tok->type == TOK_YIELD)?      "yield" :
    (tok->type == TOK_TRY)?        "try" :
    (tok->type == TOK_EXCEPT)?     "except" :
    (tok->type == TOK_RAISE)?      "raise" :
    (tok->type == TOK_RETURN)?     "return" :
    (tok->type == TOK_INTEGER)?    "integer" :
    (tok->type == TOK_UNSIGNED)?   "unsigned" :
    (tok->type == TOK_FLOAT)?      "float" :
    (tok->type == TOK_STRING)?     "string" :
    (tok->type == TOK_DICT)?       "dictionary" :
    (tok->type == TOK_ARRAY)?      "array" :
    (tok->type == TOK_BOOL)?       "boolean" :
    (tok->type == TOK_NOTHING)?    "nothing" :
    (tok->type == TOK_EXIT)?        "exit" :
    (tok->type == TOK_FINALLY)?    "finally" : "UNKNOWN";
}

void print_token(token_t* tok) {

    if(tok != NULL) {
    printf("tok text \"%s\": type \"%s\" ", raw_string(tok->text), token_type_to_str(tok));
        printf("file \"%s\": line %d: column %d\n", raw_string(tok->fname), tok->line_no, tok->col_no);
    }
    else
        printf("NULL TOKEN\n");
}

