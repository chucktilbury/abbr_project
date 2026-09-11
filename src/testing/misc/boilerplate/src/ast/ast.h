
/*
 *  This is a generated file
 */
#ifndef _AST_H_
#define _AST_H_

//#include "tokens.h"

typedef enum {
    AST_MODULE = 512,
    AST_START_CLAUSE = 513,
    AST_MODULE_ITEM = 514,
    AST_INCLUDE_STATEMENT = 515,
    AST_IMPORT_STATEMENT = 516,
    AST_IDENTIFIER = 517,
    AST_NAMESPACE_ITEM = 518,
    AST_GLOBAL_SCOPE_OPERATOR = 519,
    AST_CLASS_SCOPE_OPERATOR = 520,
    AST_NAMESPACE = 521,
    AST_CLASS_DEFINITION = 522,
    AST_INHERITANCE_ITEM = 523,
    AST_CLASS_ITEM = 524,
    AST_FUNCTION_DECLARATION = 525,
    AST_CONSTRUCTOR_DECLARATION = 526,
    AST_DESTRUCTOR_DECLARATION = 527,
    AST_FUNCTION_DEFINITION_PARAMETERS = 528,
    AST_FUNCTION_DECL_PARAMETER = 529,
    AST_FUNCTION_DECLARATION_PARAMETERS = 530,
    AST_LITERAL_TYPE = 531,
    AST_TYPE_SPECIFIER = 532,
    AST_FUNCTION_DEFINITION = 533,
    AST_CONSTRUCTOR_DEFINITION = 534,
    AST_DESTRUCTOR_DEFINITION = 535,
    AST_DATA_DECLARATION = 536,
    AST_COMPOUND_NAME = 537,
    AST_LITERAL_NUMBER = 538,
    AST_STRING_LITERAL = 539,
    AST_CONST_VALUE = 540,
    AST_LITERAL_STRING = 541,
    AST_FORMATTED_STRING = 542,
    AST_LITERAL_ARRAY_DEFINITION = 543,
    AST_LITERAL_DICT_ITEM = 544,
    AST_LITERAL_DICT_DEFINITION = 545,
    AST_PRIMARY_EXPRESSION = 546,
    AST_EXPRESSION = 547,
    AST_COMPOUND_REFERENCE = 548,
    AST_COMPOUND_REFERENCE_ITEM = 549,
    AST_FUNCTION_REFERENCE = 550,
    AST_ARRAY_REFERENCE = 551,
    AST_ARRAY_PARAMETERS = 552,
    AST_FUNCTION_BODY_ITEM = 553,
    AST_INLINE_STATEMENT = 554,
    AST_RAISE_STATEMENT = 555,
    AST_FLOW_STATEMENT = 556,
    AST_LOOP_BODY_ITEM = 557,
    AST_BREAK_STATEMENT = 558,
    AST_CONTINUE_STATEMENT = 559,
    AST_YIELD_STATEMENT = 560,
    AST_LOOP_BODY = 561,
    AST_FUNCTION_BODY = 562,
    AST_ASSIGNMENT = 563,
    AST_DATA_DEFINITION = 564,
    AST_RETURN_STATEMENT = 565,
    AST_IF_CLAUSE = 566,
    AST_ELSE_CLAUSE = 567,
    AST_FINAL_ELSE_CLAUSE = 568,
    AST_FOR_CLAUSE = 569,
    AST_WHILE_CLAUSE = 570,
    AST_DO_CLAUSE = 571,
    AST_TRY_CLAUSE = 572,
    AST_EXCEPT_CLAUSE = 573,
    AST_FINALLY_CLAUSE = 574,
    AST_EXIT_STATEMENT = 575,
} ast_type_t;

typedef struct _ast_node_t {
    ast_type_t type;
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

    // objects
} ast_module_t;


/*
 *  start_clause
 *      : 'start' function_body
 *      ;
 */
typedef struct _ast_start_clause_t {
    ast_node_t node;

    // objects
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

    // objects
} ast_module_item_t;


/*
 *  include_statement
 *      : 'include' string_literal
 *      ;
 */
typedef struct _ast_include_statement_t {
    ast_node_t node;

    // objects
} ast_include_statement_t;


/*
 *  import_statement
 *      : 'import' string_literal
 *      | 'import' compound_name ( ('from' string_literal)? ('as' identifier)? )?
 *      ;
 */
typedef struct _ast_import_statement_t {
    ast_node_t node;

    // objects
} ast_import_statement_t;


/*
 *  identifier
 *      : IDENTIFIER
 *      ;
 */
typedef struct _ast_identifier_t {
    ast_node_t node;

    // objects
} ast_identifier_t;


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

    // objects
} ast_namespace_item_t;


/*
 *  global_scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 */
typedef struct _ast_global_scope_operator_t {
    ast_node_t node;

    // objects
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

    // objects
} ast_class_scope_operator_t;


/*
 *  namespace
 *      : 'namespace' identifier '{' namespace_item* '}'
 *      ;
 */
typedef struct _ast_namespace_t {
    ast_node_t node;

    // objects
} ast_namespace_t;


/*
 *  class_definition
 *      : 'class' identifier ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
 *      ;
 */
typedef struct _ast_class_definition_t {
    ast_node_t node;

    // objects
} ast_class_definition_t;


/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 */
typedef struct _ast_inheritance_item_t {
    ast_node_t node;

    // objects
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

    // objects
} ast_class_item_t;


/*
 *  function_declaration
 *      : type_specifier identifier function_declaration_parameters function_body?
 *      ;
 */
typedef struct _ast_function_declaration_t {
    ast_node_t node;

    // objects
} ast_function_declaration_t;


/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters function_body?
 *      ;
 */
typedef struct _ast_constructor_declaration_t {
    ast_node_t node;

    // objects
} ast_constructor_declaration_t;


/*
 *  destructor_declaration
 *      : 'destroy' function_body?
 *      ;
 */
typedef struct _ast_destructor_declaration_t {
    ast_node_t node;

    // objects
} ast_destructor_declaration_t;


/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 */
typedef struct _ast_function_definition_parameters_t {
    ast_node_t node;

    // objects
} ast_function_definition_parameters_t;


/*
 *  function_decl_parameter
 *      : type_specifier (identifier)?
 *      ;
 */
typedef struct _ast_function_decl_parameter_t {
    ast_node_t node;

    // objects
} ast_function_decl_parameter_t;


/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 */
typedef struct _ast_function_declaration_parameters_t {
    ast_node_t node;

    // objects
} ast_function_declaration_parameters_t;


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

    // objects
} ast_literal_type_t;


/*
 *  type_specifier
 *      : literal_type
 *      | compound_name
 *      ;
 */
typedef struct _ast_type_specifier_t {
    ast_node_t node;

    // objects
} ast_type_specifier_t;


/*
 *  function_definition
 *      : type_specifier identifier '.' identifier function_definition_parameters function_body
 *      ;
 */
typedef struct _ast_function_definition_t {
    ast_node_t node;

    // objects
} ast_function_definition_t;


/*
 *  constructor_definition
 *      : identifier '.' 'create' function_definition_parameters function_body
 *      ;
 */
typedef struct _ast_constructor_definition_t {
    ast_node_t node;

    // objects
} ast_constructor_definition_t;


/*
 *  destructor_definition
 *      : identifier '.' 'destroy' function_body
 *      ;
 */
typedef struct _ast_destructor_definition_t {
    ast_node_t node;

    // objects
} ast_destructor_definition_t;


/*
 *  data_declaration
 *      : type_specifier identifier ( '=' const_value )?
 *      ;
 */
typedef struct _ast_data_declaration_t {
    ast_node_t node;

    // objects
} ast_data_declaration_t;


/*
 *  compound_name
 *      : identifier ('.' identifier)*
 *      ;
 */
typedef struct _ast_compound_name_t {
    ast_node_t node;

    // objects
} ast_compound_name_t;


/*
 *  literal_number
 *      : LITERAL_INT
 *      | LITERAL_UNS
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      ;
 */
typedef struct _ast_literal_number_t {
    ast_node_t node;

    // objects
} ast_literal_number_t;


/*
 *  string_literal
 *      : LITERAL_SSTR
 *      | LITERAL_DSTR
 *      ;
 */
typedef struct _ast_string_literal_t {
    ast_node_t node;

    // objects
} ast_string_literal_t;


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

    // objects
} ast_const_value_t;


/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 */
typedef struct _ast_literal_string_t {
    ast_node_t node;

    // objects
} ast_literal_string_t;


/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
typedef struct _ast_formatted_string_t {
    ast_node_t node;

    // objects
} ast_formatted_string_t;


/*
 *  literal_array_definition
 *      : '[' const_value (',' const_value)* ']'
 *      ;
 */
typedef struct _ast_literal_array_definition_t {
    ast_node_t node;

    // objects
} ast_literal_array_definition_t;


/*
 *  literal_dict_item
 *      : string_literal ':' const_value
 *      ;
 */
typedef struct _ast_literal_dict_item_t {
    ast_node_t node;

    // objects
} ast_literal_dict_item_t;


/*
 *  literal_dict_definition
 *      : '[' literal_dict_item (',' literal_dict_item)* ']'
 *      ;
 */
typedef struct _ast_literal_dict_definition_t {
    ast_node_t node;

    // objects
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

    // objects
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

    // objects
} ast_expression_t;


/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 */
typedef struct _ast_compound_reference_t {
    ast_node_t node;

    // objects
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

    // objects
} ast_compound_reference_item_t;


/*
 *  function_reference
 *      : identifier '(' expression (',' expression)* ')'
 *      ;
 */
typedef struct _ast_function_reference_t {
    ast_node_t node;

    // objects
} ast_function_reference_t;


/*
 *  array_reference
 *      : identifier array_parameters (array_parameters)*
 *      ;
 */
typedef struct _ast_array_reference_t {
    ast_node_t node;

    // objects
} ast_array_reference_t;


/*
 *  array_parameters
 *      : '[' (array_parameters | expression) ']'
 *      ;
 */
typedef struct _ast_array_parameters_t {
    ast_node_t node;

    // objects
} ast_array_parameters_t;


/*
 *  function_body_item
 *      : compound_reference
 *      | assignment
 *      | data_definition
 *      | flow_statement
 *      | exit_statement
 *      | raise_statement
 *      | return_statement
 *      | inline_statement
 *      ;
 */
typedef struct _ast_function_body_item_t {
    ast_node_t node;

    // objects
} ast_function_body_item_t;


/*
 *  inline_statement
 *      : 'inline' '{' RAW_TEXT '}'
 *      ;
 */
typedef struct _ast_inline_statement_t {
    ast_node_t node;

    // objects
} ast_inline_statement_t;


/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 */
typedef struct _ast_raise_statement_t {
    ast_node_t node;

    // objects
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

    // objects
} ast_flow_statement_t;


/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | break_statement
 *      | continue_statement
 *      ;
 */
typedef struct _ast_loop_body_item_t {
    ast_node_t node;

    // objects
} ast_loop_body_item_t;


/*
 *  break_statement
 *      : 'break'
 *      ;
 */
typedef struct _ast_break_statement_t {
    ast_node_t node;

    // objects
} ast_break_statement_t;


/*
 *  continue_statement
 *      : 'continue'
 *      ;
 */
typedef struct _ast_continue_statement_t {
    ast_node_t node;

    // objects
} ast_continue_statement_t;


/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 */
typedef struct _ast_yield_statement_t {
    ast_node_t node;

    // objects
} ast_yield_statement_t;


/*
 *  loop_body
 *      : '{' (loop_body_item | loop_body)* '}'
 *      ;
 */
typedef struct _ast_loop_body_t {
    ast_node_t node;

    // objects
} ast_loop_body_t;


/*
 *  function_body
 *      : '{' (function_body_item | function_body)+ '}'
 *      ;
 */
typedef struct _ast_function_body_t {
    ast_node_t node;

    // objects
} ast_function_body_t;


/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 */
typedef struct _ast_assignment_t {
    ast_node_t node;

    // objects
} ast_assignment_t;


/*
 *  data_definition
 *      : type_specifier identifier ( '=' expression )?
 *      ;
 */
typedef struct _ast_data_definition_t {
    ast_node_t node;

    // objects
} ast_data_definition_t;


/*
 *  return_statement
 *      : 'return' ( '(' expression? ')' )?
 *      ;
 */
typedef struct _ast_return_statement_t {
    ast_node_t node;

    // objects
} ast_return_statement_t;


/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 */
typedef struct _ast_if_clause_t {
    ast_node_t node;

    // objects
} ast_if_clause_t;


/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 */
typedef struct _ast_else_clause_t {
    ast_node_t node;

    // objects
} ast_else_clause_t;


/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 */
typedef struct _ast_final_else_clause_t {
    ast_node_t node;

    // objects
} ast_final_else_clause_t;


/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? identifier)? )? ')' )? loop_body
 *      ;
 */
typedef struct _ast_for_clause_t {
    ast_node_t node;

    // objects
} ast_for_clause_t;


/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
typedef struct _ast_while_clause_t {
    ast_node_t node;

    // objects
} ast_while_clause_t;


/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 */
typedef struct _ast_do_clause_t {
    ast_node_t node;

    // objects
} ast_do_clause_t;


/*
 *  try_clause
 *      : 'try' function_body ( except_clause )+ finally_clause?
 *      ;
 */
typedef struct _ast_try_clause_t {
    ast_node_t node;

    // objects
} ast_try_clause_t;


/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' identifier)? ')' function_body
 *      ;
 */
typedef struct _ast_except_clause_t {
    ast_node_t node;

    // objects
} ast_except_clause_t;


/*
 *  finally_clause
 *      : 'finally' function_body
 *      ;
 */
typedef struct _ast_finally_clause_t {
    ast_node_t node;

    // objects
} ast_finally_clause_t;


/*
 *  exit_statement
 *      : 'exit' '(' expression? ')'
 *      ;
 */
typedef struct _ast_exit_statement_t {
    ast_node_t node;

    // objects
} ast_exit_statement_t;



ast_node_t* create_ast_node(ast_type_t type);
void traverse_ast(ast_node_t* node);
const char* node_type_to_str(ast_type_t type);
size_t get_node_size(ast_type_t type);

void _traverse_module(ast_module_t* node);
void _traverse_start_clause(ast_start_clause_t* node);
void _traverse_module_item(ast_module_item_t* node);
void _traverse_include_statement(ast_include_statement_t* node);
void _traverse_import_statement(ast_import_statement_t* node);
void _traverse_identifier(ast_identifier_t* node);
void _traverse_namespace_item(ast_namespace_item_t* node);
void _traverse_global_scope_operator(ast_global_scope_operator_t* node);
void _traverse_class_scope_operator(ast_class_scope_operator_t* node);
void _traverse_namespace(ast_namespace_t* node);
void _traverse_class_definition(ast_class_definition_t* node);
void _traverse_inheritance_item(ast_inheritance_item_t* node);
void _traverse_class_item(ast_class_item_t* node);
void _traverse_function_declaration(ast_function_declaration_t* node);
void _traverse_constructor_declaration(ast_constructor_declaration_t* node);
void _traverse_destructor_declaration(ast_destructor_declaration_t* node);
void _traverse_function_definition_parameters(ast_function_definition_parameters_t* node);
void _traverse_function_decl_parameter(ast_function_decl_parameter_t* node);
void _traverse_function_declaration_parameters(ast_function_declaration_parameters_t* node);
void _traverse_literal_type(ast_literal_type_t* node);
void _traverse_type_specifier(ast_type_specifier_t* node);
void _traverse_function_definition(ast_function_definition_t* node);
void _traverse_constructor_definition(ast_constructor_definition_t* node);
void _traverse_destructor_definition(ast_destructor_definition_t* node);
void _traverse_data_declaration(ast_data_declaration_t* node);
void _traverse_compound_name(ast_compound_name_t* node);
void _traverse_literal_number(ast_literal_number_t* node);
void _traverse_string_literal(ast_string_literal_t* node);
void _traverse_const_value(ast_const_value_t* node);
void _traverse_literal_string(ast_literal_string_t* node);
void _traverse_formatted_string(ast_formatted_string_t* node);
void _traverse_literal_array_definition(ast_literal_array_definition_t* node);
void _traverse_literal_dict_item(ast_literal_dict_item_t* node);
void _traverse_literal_dict_definition(ast_literal_dict_definition_t* node);
void _traverse_primary_expression(ast_primary_expression_t* node);
void _traverse_expression(ast_expression_t* node);
void _traverse_compound_reference(ast_compound_reference_t* node);
void _traverse_compound_reference_item(ast_compound_reference_item_t* node);
void _traverse_function_reference(ast_function_reference_t* node);
void _traverse_array_reference(ast_array_reference_t* node);
void _traverse_array_parameters(ast_array_parameters_t* node);
void _traverse_function_body_item(ast_function_body_item_t* node);
void _traverse_inline_statement(ast_inline_statement_t* node);
void _traverse_raise_statement(ast_raise_statement_t* node);
void _traverse_flow_statement(ast_flow_statement_t* node);
void _traverse_loop_body_item(ast_loop_body_item_t* node);
void _traverse_break_statement(ast_break_statement_t* node);
void _traverse_continue_statement(ast_continue_statement_t* node);
void _traverse_yield_statement(ast_yield_statement_t* node);
void _traverse_loop_body(ast_loop_body_t* node);
void _traverse_function_body(ast_function_body_t* node);
void _traverse_assignment(ast_assignment_t* node);
void _traverse_data_definition(ast_data_definition_t* node);
void _traverse_return_statement(ast_return_statement_t* node);
void _traverse_if_clause(ast_if_clause_t* node);
void _traverse_else_clause(ast_else_clause_t* node);
void _traverse_final_else_clause(ast_final_else_clause_t* node);
void _traverse_for_clause(ast_for_clause_t* node);
void _traverse_while_clause(ast_while_clause_t* node);
void _traverse_do_clause(ast_do_clause_t* node);
void _traverse_try_clause(ast_try_clause_t* node);
void _traverse_except_clause(ast_except_clause_t* node);
void _traverse_finally_clause(ast_finally_clause_t* node);
void _traverse_exit_statement(ast_exit_statement_t* node);

#endif /* _AST_H_ */


