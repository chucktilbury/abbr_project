
/*
 *  This is a generated file
 */
#ifndef _AST_H_
#define _AST_H_

typedef enum {
    AST_MODULE = 512,
    AST_START_CLAUSE = 513,
    AST_MODULE_ITEM = 514,
    AST_INCLUDE_STATEMENT = 515,
    AST_IMPORT_STATEMENT = 516,
    AST_NAMESPACE_ITEM = 517,
    AST_GLOBAL_SCOPE_OPERATOR = 518,
    AST_CLASS_SCOPE_OPERATOR = 519,
    AST_NAMESPACE = 520,
    AST_CLASS_DEFINITION = 521,
    AST_INHERITANCE_ITEM = 522,
    AST_CLASS_ITEM = 523,
    AST_FUNCTION_DECLARATION = 524,
    AST_CONSTRUCTOR_DECLARATION = 525,
    AST_DESTRUCTOR_DECLARATION = 526,
    AST_FUNCTION_DEFINITION_PARAMETERS = 527,
    AST_FUNCTION_DECL_PARAMETER = 528,
    AST_FUNCTION_DECLARATION_PARAMETERS = 529,
    AST_TYPE_SPECIFIER = 530,
    AST_FUNCTION_DEFINITION = 531,
    AST_CONSTRUCTOR_DEFINITION = 532,
    AST_DESTRUCTOR_DEFINITION = 533,
    AST_DATA_DECLARATION = 534,
    AST_COMPOUND_NAME = 535,
    AST_CONST_VALUE = 536,
    AST_LITERAL_STRING = 537,
    AST_FORMATTED_STRING = 538,
    AST_LITERAL_ARRAY_DEFINITION = 539,
    AST_LITERAL_DICT_ITEM = 540,
    AST_LITERAL_DICT_DEFINITION = 541,
    AST_PRIMARY_EXPRESSION = 542,
    AST_EXPRESSION = 543,
    AST_COMPOUND_REFERENCE = 544,
    AST_COMPOUND_REFERENCE_ITEM = 545,
    AST_FUNCTION_REFERENCE = 546,
    AST_ARRAY_REFERENCE = 547,
    AST_ARRAY_PARAMETERS = 548,
    AST_FUNCTION_BODY_ITEM = 549,
    AST_RAISE_STATEMENT = 550,
    AST_FLOW_STATEMENT = 551,
    AST_LOOP_BODY_ITEM = 552,
    AST_YIELD_STATEMENT = 553,
    AST_LOOP_BODY = 554,
    AST_FUNCTION_BODY = 555,
    AST_ASSIGNMENT = 556,
    AST_DATA_DEFINITION = 557,
    AST_RETURN_STATEMENT = 558,
    AST_IF_CLAUSE = 559,
    AST_ELSE_CLAUSE = 560,
    AST_FINAL_ELSE_CLAUSE = 561,
    AST_FOR_CLAUSE = 562,
    AST_WHILE_CLAUSE = 563,
    AST_DO_CLAUSE = 564,
    AST_TRY_CLAUSE = 565,
    AST_EXCEPT_CLAUSE = 566,
    AST_FINALLY_CLAUSE = 567,
    AST_EXIT_STATEMENT = 568,
    AST_OPERATOR = 569,
    AST_BREAK_STATEMENT = 570,
    AST_CONTINUE_STATEMENT = 571,
    AST_INLINE_STATEMENT = 572,
    AST_LITERAL_NUMBER = 573,
    AST_STRING_LITERAL = 574,
    AST_LITERAL_TYPE = 575,
    AST_IDENTIFIER = 576,
    AST_INHERITANCE_LIST = 577,
    AST_CLASS_BODY = 578,
    AST_TYPE_CAST = 578,
} ast_type_t;

#include "ast_struct.h"
#include "traverse.h"

// ast function interface
ast_node_t* create_ast_node(ast_type_t type);
void destroy_ast_node(ast_node_t* node);
const char* node_type_to_str(ast_type_t type);

// node list functions base on pointer_list
ast_node_list_t* create_ast_node_list(void);
void destroy_ast_node_list(ast_node_list_t* lst);
void append_ast_node_list(ast_node_list_t* lst, ast_node_t* node);
ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, int* mark);
void push_ast_node_list(ast_node_list_t* ptr, ast_node_t* node);
ast_node_t* pop_ast_node_list(ast_node_list_t* ptr);
ast_node_t* peek_ast_node_list(ast_node_list_t* ptr);

void ast_to_dotfile(string_t* fname, ast_node_t* node);

#endif /* _AST_H_ */
