#ifndef _AST_STRUCT_H_
#define _AST_STRUCT_H_

#include "common.h"
#include "tokens.h"

typedef pointer_list_t ast_node_list_t;

typedef struct _ast_node_t {
    // ast_type_t type;
    int type;
    const char* fname;
    int line_no;
    int col_no;
} ast_node_t;

/*
 *  module
 *      : module_item*
 *      | start clause
 *      ;
 */
typedef struct _ast_module_t {
    ast_node_t node;
    ast_node_list_t* list;
    bool start_clause;
} ast_module_t;


/*
 *  start_clause
 *      : 'start' function_body
 *      ;
 */
typedef struct _ast_start_clause_t {
    ast_node_t node;
    struct _ast_function_body_t* function_body;
} ast_start_clause_t;


/*
 *  module_item
 *      : namespace_item
 *      | include_statement
 *      | import_statement
 *      ;
 */
typedef struct _ast_module_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_module_item_t;


/*
 *  include_statement
 *      : 'include' string_literal
 *      ;
 */
typedef struct _ast_include_statement_t {
    ast_node_t node;
    // include is handled outside of the AST
    struct _ast_string_literal_t* str;
} ast_include_statement_t;


/*
 *  import_statement
 *      : 'import' string_literal ('as' identifier)?
 *      ;
 */
typedef struct _ast_import_statement_t {
    ast_node_t node;
    // import is handled outside of the AST
    struct _ast_string_literal_t* str;
    struct _ast_identifier_t* identifier;
} ast_import_statement_t;


/*
 *  namespace_item
 *      : global_scope_operator
 *      | class_definition
 *      | function_definition
 *      | constructor_definition
 *      | destructor_definition
 *      | namespace
 *      ;
 */
typedef struct _ast_namespace_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_namespace_item_t;


/*
 *  scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 */
typedef struct _ast_global_scope_operator_t {
    ast_node_t node;
    token_type_t tok;
} ast_global_scope_operator_t;


/*
 *  class_scope_operator
 *      : 'public'
 *      | 'private'
 *      | 'protected'
 *      ;
 */
typedef struct _ast_class_scope_operator_t {
    ast_node_t node;
    token_type_t tok;
} ast_class_scope_operator_t;


/*
 *  namespace
 *      : 'namespace' identifier '{' namespace_item* '}'
 *      ;
 */
typedef struct _ast_namespace_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    ast_node_list_t* list;
} ast_namespace_t;


/*
 *  class_definition
 *      : 'class' identifier inheritance_list? class_body
 *      ;
 */
typedef struct _ast_class_definition_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_inheritance_list_t* i_list;
    struct _ast_class_body_t* c_list;
} ast_class_definition_t;


/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 */
typedef struct _ast_inheritance_item_t {
    ast_node_t node;
    struct _ast_compound_name_t* compound_name;
    struct _ast_class_scope_operator_t* class_scope_operator;
} ast_inheritance_item_t;


/*
 *  class_item
 *      : class_scope_operator
 *      | function_declaration
 *      | data_declaration
 *      | constructor_declaration
 *      | destructor_declaration
 *      ;
 */
typedef struct _ast_class_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_class_item_t;


/*
 *  function_declaration
 *      : type_specifier identifier function_declaration_parameters function_body?
 *      ;
 */
typedef struct _ast_function_declaration_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_function_declaration_parameters_t* function_declaration_parameters;
    struct _ast_function_body_t* func_body;
} ast_function_declaration_t;


/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters function_body?
 *      ;
 */
typedef struct _ast_constructor_declaration_t {
    ast_node_t node;
    struct _ast_function_declaration_parameters_t* function_declaration_parameters;
    struct _ast_function_body_t* func_body;
} ast_constructor_declaration_t;


/*
 *  destructor_declaration
 *      : 'destroy' function_body?
 *      ;
 */
typedef struct _ast_destructor_declaration_t {
    ast_node_t node;
    struct _ast_function_body_t* func_body;
} ast_destructor_declaration_t;


/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 */
typedef struct _ast_function_definition_parameters_t {
    ast_node_t node;
    ast_node_list_t* data_declaration;
} ast_function_definition_parameters_t;


/*
 *  function_decl_parameter
 *      : type_specifier (identifier)?
 *      ;
 */
typedef struct _ast_function_decl_parameter_t {
    ast_node_t node;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_identifier_t* identifier;
} ast_function_decl_parameter_t;


/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 */
typedef struct _ast_function_declaration_parameters_t {
    ast_node_t node;
    ast_node_list_t* item;
} ast_function_declaration_parameters_t;


/*
 *  type_specifier
 *      : literal_type
 *      | compound_name
 *      ;
 */
typedef struct _ast_type_specifier_t {
    ast_node_t node;
    ast_node_t* item;
} ast_type_specifier_t;


/*
 *  function_definition
 *      : type_specifier identifier '.' identifier function_definition_parameters function_body
 *      ;
 */
typedef struct _ast_function_definition_t {
    ast_node_t node;
    struct _ast_identifier_t* group;
    struct _ast_identifier_t* name;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_function_definition_parameters_t* function_definition_parameters;
    struct _ast_function_body_t* function_body;
} ast_function_definition_t;


/*
 *  constructor_definition
 *      : identifier '.' 'create' function_definition_parameters function_body
 *      ;
 */
typedef struct _ast_constructor_definition_t {
    ast_node_t node;
    struct _ast_identifier_t* group;
    struct _ast_function_definition_parameters_t* function_definition_parameters;
    struct _ast_function_body_t* function_body;
} ast_constructor_definition_t;


/*
 *  destructor_definition
 *      : identifier '.' 'destroy' function_body
 *      ;
 */
typedef struct _ast_destructor_definition_t {
    ast_node_t node;
    struct _ast_identifier_t* group;
    struct _ast_function_body_t* function_body;
} ast_destructor_definition_t;


/*
 *  data_declaration
 *      : type_specifier identifier ( '=' const_value )?
 *      ;
 */
typedef struct _ast_data_declaration_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_const_value_t* const_value;
} ast_data_declaration_t;


/*
 *  compound_name
 *      : identifier ('.' identifier)*
 *      ;
 */
typedef struct _ast_compound_name_t {
    ast_node_t node;
    ast_node_list_t* list;
} ast_compound_name_t;


/*
 *  const_value
 *      : literal_number
 *      | string_literal
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 */
typedef struct _ast_const_value_t {
    ast_node_t node;
    ast_node_t* item;
} ast_const_value_t;


/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 */
typedef struct _ast_literal_string_t {
    ast_node_t node;
    string_t* literal_str;
    struct _ast_formatted_string_t* formatted_string;
} ast_literal_string_t;


/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
typedef struct _ast_formatted_string_t {
    ast_node_t node;
    string_t* literal_str;
    ast_node_list_t* list;
} ast_formatted_string_t;


/*
 *  literal_array_definition
 *      : '[' const_value (',' const_value)* ']'
 *      ;
 */
typedef struct _ast_literal_array_definition_t {
    ast_node_t node;
    ast_node_list_t* const_value;
} ast_literal_array_definition_t;


/*
 *  literal_dict_item
 *      : string_literal ':' const_value
 *      ;
 */
typedef struct _ast_literal_dict_item_t {
    ast_node_t node;
    struct _ast_string_literal_t* literal_str;
    struct _ast_const_value_t* const_value;
} ast_literal_dict_item_t;


/*
 *  literal_dict_definition
 *      : '[' ( literal_dict_item (',' literal_dict_item)* )? ']'
 *      ;
 */
typedef struct _ast_literal_dict_definition_t {
    ast_node_t node;
    ast_node_list_t* literal_dict_item;
} ast_literal_dict_definition_t;


/*
 *  primary_expression
 *      : literal_number
 *      | literal_string
 *      | compound_reference
 *      ;
 */
typedef struct _ast_primary_expression_t {
    ast_node_t node;
    ast_node_t* value;
} ast_primary_expression_t;


/*
 *  expression
 *      : expression ('*' | '/' | '%') expression
 *      | expression '^' expression
 *      | expression ('+' | '-') expression
 *      | expression ('<' | '>' | '<=' | '>=' | 'lt' | 'gt' | 'lte' | 'gte') expression
 *      | expression ('==' | '!=' | 'equ' | 'neq' ) expression
 *      | expression ('&&' | 'and') expression
 *      | expression ('||' | 'or') expression
 *      | ('!' | 'not' | '-') expression
 *      | '(' expression ')'
 *      | primary_expression
 *      ;
 */
typedef struct _ast_expression_t {
    ast_node_t node;
    // Note that expressions are parsed differently than the other
    // non-terminals. Tree has either ast_operator_t or
    // ast_primary_expression_t elements in it.
    ast_node_t* tree;
} ast_expression_t;


/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 */
typedef struct _ast_compound_reference_t {
    ast_node_t node;
    ast_node_list_t* list;
} ast_compound_reference_t;


/*
 *  compound_reference_item
 *      : identifier
 *      | function_reference
 *      | array_reference
 *      ;
 */
typedef struct _ast_compound_reference_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_compound_reference_item_t;


/*
 *  function_reference
 *      : identifier '(' expression (',' expression)* ')'
 *      ;
 */
typedef struct _ast_function_reference_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    ast_node_list_t* expr;
} ast_function_reference_t;


/*
 *  array_reference
 *      : identifier array_parameters (array_parameters)*
 *      ;
 */
typedef struct _ast_array_reference_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    ast_node_list_t* array_parameters;
} ast_array_reference_t;


/*
 *  array_parameters
 *      : '[' (array_parameters | expression) ']'
 *      ;
 */
typedef struct _ast_array_parameters_t {
    ast_node_t node;
    ast_node_t* item;
} ast_array_parameters_t;


/*
 *  function_body_item
 *      : compound_reference
 *      | assignment
 *      | data_definition
 *      | flow_statement
 *      | print_statement
 *      | exit_statement
 *      | raise_statement
 *      | return_statement
 *      | inline_statement
 *      | function_body
 *      ;
 */
typedef struct _ast_function_body_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_function_body_item_t;


/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 */
typedef struct _ast_raise_statement_t {
    ast_node_t node;
    struct _ast_compound_name_t* compound_name;
} ast_raise_statement_t;


/*
 *  flow_statement
 *      : if_clause
 *      | for_clause
 *      | while_clause
 *      | do_clause
 *      | try_clause
 *      ;
 */
typedef struct _ast_flow_statement_t {
    ast_node_t node;
    ast_node_t* item;
} ast_flow_statement_t;


/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | break_statement
 *      | continue_statement
 *      | loop_body
 *      ;
 */
typedef struct _ast_loop_body_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_loop_body_item_t;


/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 */
typedef struct _ast_yield_statement_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
} ast_yield_statement_t;


/*
 *  loop_body
 *      : '{' loop_body_item* '}'
 *      ;
 */
typedef struct _ast_loop_body_t {
    ast_node_t node;
    ast_node_list_t* item;
} ast_loop_body_t;


/*
 *  function_body
 *      : '{' function_body_item+ '}'
 *      ;
 */
typedef struct _ast_function_body_t {
    ast_node_t node;
    ast_node_list_t* item;
} ast_function_body_t;


/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 */
typedef struct _ast_assignment_t {
    ast_node_t node;
    struct _ast_compound_reference_t* compound_reference;
    struct _ast_expression_t* expression;
} ast_assignment_t;


/*
 *  data_definition
 *      : type_specifier identifier ( '=' expression )?
 *      ;
 */
typedef struct _ast_data_definition_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_expression_t* expression;
} ast_data_definition_t;


/*
 *  return_statement
 *      : 'return' ( '(' expression? ')' )?
 *      ;
 */
typedef struct _ast_return_statement_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
} ast_return_statement_t;


/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 */
typedef struct _ast_if_clause_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
    struct _ast_function_body_t* function_body;
    struct _ast_final_else_clause_t* final_else_clause;
    ast_node_list_t* else_clause;
} ast_if_clause_t;


/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 */
typedef struct _ast_else_clause_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
    struct _ast_function_body_t* function_body;
} ast_else_clause_t;


/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 */
typedef struct _ast_final_else_clause_t {
    ast_node_t node;
    struct _ast_function_body_t* function_body;
} ast_final_else_clause_t;


/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? identifier)? )? ')' )? loop_body
 *      ;
 */
typedef struct _ast_for_clause_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_expression_t* expr;
    struct _ast_type_specifier_t* type_specifier;
    struct _ast_loop_body_t* loop_body;
} ast_for_clause_t;


/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
typedef struct _ast_while_clause_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
    struct _ast_loop_body_t* loop_body;
} ast_while_clause_t;


/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 */
typedef struct _ast_do_clause_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
    struct _ast_loop_body_t* loop_body;
} ast_do_clause_t;


/*
 *  try_clause
 *      : 'try' function_body except_clause+ finally_clause?
 *      ;
 */
typedef struct _ast_try_clause_t {
    ast_node_t node;
    struct _ast_function_body_t* function_body;
    struct _ast_finally_clause_t* finally_clause;
    ast_node_list_t* except_clause;
} ast_try_clause_t;


/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' identifier)? ')' function_body
 *      ;
 */
typedef struct _ast_except_clause_t {
    ast_node_t node;
    struct _ast_identifier_t* identifier;
    struct _ast_compound_name_t* compound_name;
    struct _ast_function_body_t* function_body;
} ast_except_clause_t;


/*
 *  finally_clause
 *      : 'finally' function_body
 *      ;
 */
typedef struct _ast_finally_clause_t {
    ast_node_t node;
    struct _ast_function_body_t* function_body;
} ast_finally_clause_t;

/*
 *  exit_statement
 *      : 'exit' '(' expression? ')'
 *      ;
 */
typedef struct _ast_exit_statement_t {
    ast_node_t node;
    struct _ast_expression_t* expr;
} ast_exit_statement_t;

/*
 * generated by parser
 */
typedef struct _ast_operator_t {
    ast_node_t node;
    token_type_t oper;
    bool is_unary;
    ast_node_t* left;
    ast_node_t* right;
} ast_operator_t;

/*
 * inline_statement
 *      : 'inline' '{' RAW_TEXT '}'
 *      ;
 */
typedef struct _ast_inline_statement_t {
    ast_node_t node;
    string_t* str;
} ast_inline_statement_t;

/*
 *  break_statement
 *      : 'break'
 *      ;
 */
typedef struct _ast_break_statement_t {
    ast_node_t node;
} ast_break_statement_t;

/*
 *  continue_statement
 *      : 'continue'
 *      ;
 */
typedef struct _ast_continue_statement_t {
    ast_node_t node;
} ast_continue_statement_t;

/*
 *  string_literal
 *      : LITERAL_DSTR
 *      | LITERAL_SSTR
 *      ;
 */
typedef struct _ast_string_literal_t {
    ast_node_t node;
    string_t* str;
} ast_string_literal_t;

/*
 *  literal_number
 *      : LITERAL_INT
 *      | LITERAL_UINT
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      ;
 */
typedef struct _ast_literal_number_t {
    ast_node_t node;
    token_type_t value_type;
    union {
        long inum;
        unsigned long unum;
        double fnum;
        unsigned char bnum;
    } value;
} ast_literal_number_t;

/*
 *  literal_type
 *      : ('integer' | 'int')
 *      | ('boolean' | 'bool')
 *      | 'string'
 *      | 'dict'
 *      | 'list'
 *      | 'unsigned'
 *      | 'float'
 *      | 'nothing'
 *      ;
 */
typedef struct _ast_literal_type_t {
    ast_node_t node;
    token_type_t type;
} ast_literal_type_t;

/*
 *  identifier
 *      : IDENTIFIER
 *      ;
 */
typedef struct _ast_identifier_t {
    ast_node_t node;
    string_t* name;
} ast_identifier_t;

/*
 *  inheritance_list
 *      : '(' ( inheritance_item (',' inheritance_item)* )? ')'
 *      ;
 */
typedef struct _ast_inheritance_list_t {
    ast_node_t node;
    ast_node_list_t* list;
} ast_inheritance_list_t;

/*
 *  class_body
 *      : '{' class_item+ '}'
 *      ;
 */
typedef struct _ast_class_body_t {
    ast_node_t node;
    ast_node_list_t* list;
} ast_class_body_t;

/*
 *
 *  type_cast
 *      : '(' type_specifier ')' expression
 *      ;
 */
typedef struct _ast_type_cast_t {
    ast_node_t node;
    struct _ast_type_specifier_t* type;
    struct _ast_expression_t* expr;
} ast_type_cast_t;

#endif /* _AST_STRUCT_H_ */
