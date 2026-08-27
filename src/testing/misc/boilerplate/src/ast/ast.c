
/*
 * This is a generated file
 */
#include <stddef.h>
#include "ast.h"
#include "common.h"



/*
 *  module
 *      : module_item*
 *      | start clause
 *      ;
 */
void _traverse_module(ast_module_t* node) {
    ENTER;
    RETURN();
}



/*
 *  start_clause
 *      : 'start' function_body
 *      ;
 */
void _traverse_start_clause(ast_start_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  module_item
 *      : namespace_item
 *      | include_statement
 *      | import_statement
 *      ;
 */
void _traverse_module_item(ast_module_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  include_statement
 *      : 'include' (LITERAL_DSTR | LITERAL_SSTR)
 *      ;
 */
void _traverse_include_statement(ast_include_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  import_statement
 *      : 'import' (LITERAL_DSTR | LITERAL_SSTR)
 *      | 'import' compound_name ( ('from' (LITERAL_DSTR | LITERAL_SSTR))? ('as' IDENTIFIER)? )?
 *      ;
 */
void _traverse_import_statement(ast_import_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  namespace_item
 *      : scope_operator
 *      | class_definition
 *      | function_definition
 *      | constructor_definition
 *      | destructor_definition
 *      | namespace
 *      ;
 */
void _traverse_namespace_item(ast_namespace_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 */
void _traverse_scope_operator(ast_scope_operator_t* node) {
    ENTER;
    RETURN();
}



/*
 *  class_scope_operator
 *      : 'public'
 *      | 'private'
 *      | 'protected'
 *      ;
 */
void _traverse_class_scope_operator(ast_class_scope_operator_t* node) {
    ENTER;
    RETURN();
}



/*
 *  namespace
 *      : 'namespace' IDENTIFIER '{' namespace_item* '}'
 *      ;
 */
void _traverse_namespace(ast_namespace_t* node) {
    ENTER;
    RETURN();
}



/*
 *  class_definition
 *      : 'class' IDENTIFIER ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
 *      ;
 */
void _traverse_class_definition(ast_class_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 */
void _traverse_inheritance_item(ast_inheritance_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  class_item
 *      : class_scope_operator
 *      | function_declaration
 *      | data_declaration
 *      | constructor_declaration
 *      | destructor_declaration
 *      | function_definition
 *      ;
 */
void _traverse_class_item(ast_class_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_declaration
 *      : type_specifier IDENTIFIER function_declaration_parameters
 *      ;
 */
void _traverse_function_declaration(ast_function_declaration_t* node) {
    ENTER;
    RETURN();
}



/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters
 *      ;
 */
void _traverse_constructor_declaration(ast_constructor_declaration_t* node) {
    ENTER;
    RETURN();
}



/*
 *  destructor_declaration
 *      : 'destroy'
 *      ;
 */
void _traverse_destructor_declaration(ast_destructor_declaration_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 */
void _traverse_function_definition_parameters(ast_function_definition_parameters_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_decl_parameter
 *      : type_specifier (IDENTIFIER)?
 *      ;
 */
void _traverse_function_decl_parameter(ast_function_decl_parameter_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 */
void _traverse_function_declaration_parameters(ast_function_declaration_parameters_t* node) {
    ENTER;
    RETURN();
}



/*
 *  type_specifier
 *      : ('integer' | 'int')
 *      | ('boolean' | 'bool')
 *      | 'string'
 *      | 'dict'
 *      | 'list'
 *      | 'unsigned'
 *      | 'float'
 *      | 'nothing'
 *      | compound_name
 *      ;
 */
void _traverse_type_specifier(ast_type_specifier_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_definition
 *      : type_specifier IDENTIFIER '.' IDENTIFIER function_definition_parameters function_body
 *      ;
 */
void _traverse_function_definition(ast_function_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  constructor_definition
 *      : IDENTIFIER '.' 'create' function_definition_parameters function_body
 *      ;
 */
void _traverse_constructor_definition(ast_constructor_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  destructor_definition
 *      : IDENTIFIER '.' 'destroy' function_body
 *      ;
 */
void _traverse_destructor_definition(ast_destructor_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  data_declaration
 *      : type_specifier IDENTIFIER ( '=' const_value )?
 *      ;
 */
void _traverse_data_declaration(ast_data_declaration_t* node) {
    ENTER;
    RETURN();
}



/*
 *  compound_name
 *      : IDENTIFIER ('.' IDENTIFIER)*
 *      ;
 */
void _traverse_compound_name(ast_compound_name_t* node) {
    ENTER;
    RETURN();
}



/*
 *  const_value
 *      : LITERAL_INT
 *      | LITERAL_UNS
 *      | LITERAL_FLOAT
 *      | LITERAL_SSTR
 *      | LITERAL_DSTR
 *      | LITERAL_BOOL
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 */
void _traverse_const_value(ast_const_value_t* node) {
    ENTER;
    RETURN();
}



/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 */
void _traverse_literal_string(ast_literal_string_t* node) {
    ENTER;
    RETURN();
}



/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
void _traverse_formatted_string(ast_formatted_string_t* node) {
    ENTER;
    RETURN();
}



/*
 *  literal_array_definition
 *      : '[' const_value (',' const_value)* ']'
 *      ;
 */
void _traverse_literal_array_definition(ast_literal_array_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  literal_dict_item
 *      : (LITERAL_SSTR | LITERAL_DSTR) ':' const_value
 *      ;
 */
void _traverse_literal_dict_item(ast_literal_dict_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  literal_dict_definition
 *      : '[' literal_dict_item (',' literal_dict_item)* ']'
 *      ;
 */
void _traverse_literal_dict_definition(ast_literal_dict_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  primary_expression
 *      : LITERAL_INT
 *      | LITERAL_UNS
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      | literal_string
 *      | compound_reference
 *      ;
 */
void _traverse_primary_expression(ast_primary_expression_t* node) {
    ENTER;
    RETURN();
}



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
void _traverse_expression(ast_expression_t* node) {
    ENTER;
    RETURN();
}



/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 */
void _traverse_compound_reference(ast_compound_reference_t* node) {
    ENTER;
    RETURN();
}



/*
 *  compound_reference_item
 *      : IDENTIFIER
 *      | function_reference
 *      | array_reference
 *      ;
 */
void _traverse_compound_reference_item(ast_compound_reference_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_reference
 *      : IDENTIFIER '(' expression (',' expression)* ')'
 *      ;
 */
void _traverse_function_reference(ast_function_reference_t* node) {
    ENTER;
    RETURN();
}



/*
 *  array_reference
 *      : IDENTIFIER array_parameters (array_parameters)*
 *      ;
 */
void _traverse_array_reference(ast_array_reference_t* node) {
    ENTER;
    RETURN();
}



/*
 *  array_parameters
 *      : '[' (array_parameters | expression) ']'
 *      ;
 */
void _traverse_array_parameters(ast_array_parameters_t* node) {
    ENTER;
    RETURN();
}



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
 *      ;
 */
void _traverse_function_body_item(ast_function_body_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 */
void _traverse_raise_statement(ast_raise_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  flow_statement
 *      : if_clause
 *      | for_clause
 *      | while_clause
 *      | do_clause
 *      | try_clause
 *      ;
 */
void _traverse_flow_statement(ast_flow_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | 'break'
 *      | 'continue'
 *      ;
 */
void _traverse_loop_body_item(ast_loop_body_item_t* node) {
    ENTER;
    RETURN();
}



/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 */
void _traverse_yield_statement(ast_yield_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  loop_body
 *      : '{' (loop_body_item | loop_body)* '}'
 *      ;
 */
void _traverse_loop_body(ast_loop_body_t* node) {
    ENTER;
    RETURN();
}



/*
 *  function_body
 *      : '{' (function_body_item | function_body)+ '}'
 *      ;
 */
void _traverse_function_body(ast_function_body_t* node) {
    ENTER;
    RETURN();
}



/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 */
void _traverse_assignment(ast_assignment_t* node) {
    ENTER;
    RETURN();
}



/*
 *  data_definition
 *      : type_specifier IDENTIFIER ( '=' expression )?
 *      ;
 */
void _traverse_data_definition(ast_data_definition_t* node) {
    ENTER;
    RETURN();
}



/*
 *  return_statement
 *      : 'return' ( '(' expression? ')' )?
 *      ;
 */
void _traverse_return_statement(ast_return_statement_t* node) {
    ENTER;
    RETURN();
}



/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 */
void _traverse_if_clause(ast_if_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 */
void _traverse_else_clause(ast_else_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 */
void _traverse_final_else_clause(ast_final_else_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? IDENTIFIER)? )? ')' )? loop_body
 *      ;
 */
void _traverse_for_clause(ast_for_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
void _traverse_while_clause(ast_while_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 */
void _traverse_do_clause(ast_do_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  try_clause
 *      : 'try' function_body ( except_clause )+ finally_clause?
 *      ;
 */
void _traverse_try_clause(ast_try_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' IDENTIFIER)? ')' function_body
 *      ;
 */
void _traverse_except_clause(ast_except_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 *  finally_clause
 *      : 'finally' function_body
 *      ;
 */
void _traverse_finally_clause(ast_finally_clause_t* node) {
    ENTER;
    RETURN();
}



/*
 * Main entry point for AST traverse
 */
void traverse_ast(ast_node_t* node) {
    ENTER;
    _traverse_module((ast_module_t*)node);
    RETURN();
}

ast_node_t* create_ast_node(ast_type_t type) {

    ast_node_t* node = _ALLOC(get_node_size(type));
    node->type = type;

    return node;
}

const char* node_type_to_str(ast_type_t type) {
    return
    (type == AST_MODULE)? "ast_module_t":
    (type == AST_START_CLAUSE)? "ast_start_clause_t":
    (type == AST_MODULE_ITEM)? "ast_module_item_t":
    (type == AST_INCLUDE_STATEMENT)? "ast_include_statement_t":
    (type == AST_IMPORT_STATEMENT)? "ast_import_statement_t":
    (type == AST_NAMESPACE_ITEM)? "ast_namespace_item_t":
    (type == AST_SCOPE_OPERATOR)? "ast_scope_operator_t":
    (type == AST_CLASS_SCOPE_OPERATOR)? "ast_class_scope_operator_t":
    (type == AST_NAMESPACE)? "ast_namespace_t":
    (type == AST_CLASS_DEFINITION)? "ast_class_definition_t":
    (type == AST_INHERITANCE_ITEM)? "ast_inheritance_item_t":
    (type == AST_CLASS_ITEM)? "ast_class_item_t":
    (type == AST_FUNCTION_DECLARATION)? "ast_function_declaration_t":
    (type == AST_CONSTRUCTOR_DECLARATION)? "ast_constructor_declaration_t":
    (type == AST_DESTRUCTOR_DECLARATION)? "ast_destructor_declaration_t":
    (type == AST_FUNCTION_DEFINITION_PARAMETERS)? "ast_function_definition_parameters_t":
    (type == AST_FUNCTION_DECL_PARAMETER)? "ast_function_decl_parameter_t":
    (type == AST_FUNCTION_DECLARATION_PARAMETERS)? "ast_function_declaration_parameters_t":
    (type == AST_TYPE_SPECIFIER)? "ast_type_specifier_t":
    (type == AST_FUNCTION_DEFINITION)? "ast_function_definition_t":
    (type == AST_CONSTRUCTOR_DEFINITION)? "ast_constructor_definition_t":
    (type == AST_DESTRUCTOR_DEFINITION)? "ast_destructor_definition_t":
    (type == AST_DATA_DECLARATION)? "ast_data_declaration_t":
    (type == AST_COMPOUND_NAME)? "ast_compound_name_t":
    (type == AST_CONST_VALUE)? "ast_const_value_t":
    (type == AST_LITERAL_STRING)? "ast_literal_string_t":
    (type == AST_FORMATTED_STRING)? "ast_formatted_string_t":
    (type == AST_LITERAL_ARRAY_DEFINITION)? "ast_literal_array_definition_t":
    (type == AST_LITERAL_DICT_ITEM)? "ast_literal_dict_item_t":
    (type == AST_LITERAL_DICT_DEFINITION)? "ast_literal_dict_definition_t":
    (type == AST_PRIMARY_EXPRESSION)? "ast_primary_expression_t":
    (type == AST_EXPRESSION)? "ast_expression_t":
    (type == AST_COMPOUND_REFERENCE)? "ast_compound_reference_t":
    (type == AST_COMPOUND_REFERENCE_ITEM)? "ast_compound_reference_item_t":
    (type == AST_FUNCTION_REFERENCE)? "ast_function_reference_t":
    (type == AST_ARRAY_REFERENCE)? "ast_array_reference_t":
    (type == AST_ARRAY_PARAMETERS)? "ast_array_parameters_t":
    (type == AST_FUNCTION_BODY_ITEM)? "ast_function_body_item_t":
    (type == AST_RAISE_STATEMENT)? "ast_raise_statement_t":
    (type == AST_FLOW_STATEMENT)? "ast_flow_statement_t":
    (type == AST_LOOP_BODY_ITEM)? "ast_loop_body_item_t":
    (type == AST_YIELD_STATEMENT)? "ast_yield_statement_t":
    (type == AST_LOOP_BODY)? "ast_loop_body_t":
    (type == AST_FUNCTION_BODY)? "ast_function_body_t":
    (type == AST_ASSIGNMENT)? "ast_assignment_t":
    (type == AST_DATA_DEFINITION)? "ast_data_definition_t":
    (type == AST_RETURN_STATEMENT)? "ast_return_statement_t":
    (type == AST_IF_CLAUSE)? "ast_if_clause_t":
    (type == AST_ELSE_CLAUSE)? "ast_else_clause_t":
    (type == AST_FINAL_ELSE_CLAUSE)? "ast_final_else_clause_t":
    (type == AST_FOR_CLAUSE)? "ast_for_clause_t":
    (type == AST_WHILE_CLAUSE)? "ast_while_clause_t":
    (type == AST_DO_CLAUSE)? "ast_do_clause_t":
    (type == AST_TRY_CLAUSE)? "ast_try_clause_t":
    (type == AST_EXCEPT_CLAUSE)? "ast_except_clause_t":
    (type == AST_FINALLY_CLAUSE)? "ast_finally_clause_t":
    "UNKNOWN";
}

size_t get_node_size(ast_type_t type) {
    size_t size =
    (type == AST_MODULE)? sizeof(ast_module_t):
    (type == AST_START_CLAUSE)? sizeof(ast_start_clause_t):
    (type == AST_MODULE_ITEM)? sizeof(ast_module_item_t):
    (type == AST_INCLUDE_STATEMENT)? sizeof(ast_include_statement_t):
    (type == AST_IMPORT_STATEMENT)? sizeof(ast_import_statement_t):
    (type == AST_NAMESPACE_ITEM)? sizeof(ast_namespace_item_t):
    (type == AST_SCOPE_OPERATOR)? sizeof(ast_scope_operator_t):
    (type == AST_CLASS_SCOPE_OPERATOR)? sizeof(ast_class_scope_operator_t):
    (type == AST_NAMESPACE)? sizeof(ast_namespace_t):
    (type == AST_CLASS_DEFINITION)? sizeof(ast_class_definition_t):
    (type == AST_INHERITANCE_ITEM)? sizeof(ast_inheritance_item_t):
    (type == AST_CLASS_ITEM)? sizeof(ast_class_item_t):
    (type == AST_FUNCTION_DECLARATION)? sizeof(ast_function_declaration_t):
    (type == AST_CONSTRUCTOR_DECLARATION)? sizeof(ast_constructor_declaration_t):
    (type == AST_DESTRUCTOR_DECLARATION)? sizeof(ast_destructor_declaration_t):
    (type == AST_FUNCTION_DEFINITION_PARAMETERS)? sizeof(ast_function_definition_parameters_t):
    (type == AST_FUNCTION_DECL_PARAMETER)? sizeof(ast_function_decl_parameter_t):
    (type == AST_FUNCTION_DECLARATION_PARAMETERS)? sizeof(ast_function_declaration_parameters_t):
    (type == AST_TYPE_SPECIFIER)? sizeof(ast_type_specifier_t):
    (type == AST_FUNCTION_DEFINITION)? sizeof(ast_function_definition_t):
    (type == AST_CONSTRUCTOR_DEFINITION)? sizeof(ast_constructor_definition_t):
    (type == AST_DESTRUCTOR_DEFINITION)? sizeof(ast_destructor_definition_t):
    (type == AST_DATA_DECLARATION)? sizeof(ast_data_declaration_t):
    (type == AST_COMPOUND_NAME)? sizeof(ast_compound_name_t):
    (type == AST_CONST_VALUE)? sizeof(ast_const_value_t):
    (type == AST_LITERAL_STRING)? sizeof(ast_literal_string_t):
    (type == AST_FORMATTED_STRING)? sizeof(ast_formatted_string_t):
    (type == AST_LITERAL_ARRAY_DEFINITION)? sizeof(ast_literal_array_definition_t):
    (type == AST_LITERAL_DICT_ITEM)? sizeof(ast_literal_dict_item_t):
    (type == AST_LITERAL_DICT_DEFINITION)? sizeof(ast_literal_dict_definition_t):
    (type == AST_PRIMARY_EXPRESSION)? sizeof(ast_primary_expression_t):
    (type == AST_EXPRESSION)? sizeof(ast_expression_t):
    (type == AST_COMPOUND_REFERENCE)? sizeof(ast_compound_reference_t):
    (type == AST_COMPOUND_REFERENCE_ITEM)? sizeof(ast_compound_reference_item_t):
    (type == AST_FUNCTION_REFERENCE)? sizeof(ast_function_reference_t):
    (type == AST_ARRAY_REFERENCE)? sizeof(ast_array_reference_t):
    (type == AST_ARRAY_PARAMETERS)? sizeof(ast_array_parameters_t):
    (type == AST_FUNCTION_BODY_ITEM)? sizeof(ast_function_body_item_t):
    (type == AST_RAISE_STATEMENT)? sizeof(ast_raise_statement_t):
    (type == AST_FLOW_STATEMENT)? sizeof(ast_flow_statement_t):
    (type == AST_LOOP_BODY_ITEM)? sizeof(ast_loop_body_item_t):
    (type == AST_YIELD_STATEMENT)? sizeof(ast_yield_statement_t):
    (type == AST_LOOP_BODY)? sizeof(ast_loop_body_t):
    (type == AST_FUNCTION_BODY)? sizeof(ast_function_body_t):
    (type == AST_ASSIGNMENT)? sizeof(ast_assignment_t):
    (type == AST_DATA_DEFINITION)? sizeof(ast_data_definition_t):
    (type == AST_RETURN_STATEMENT)? sizeof(ast_return_statement_t):
    (type == AST_IF_CLAUSE)? sizeof(ast_if_clause_t):
    (type == AST_ELSE_CLAUSE)? sizeof(ast_else_clause_t):
    (type == AST_FINAL_ELSE_CLAUSE)? sizeof(ast_final_else_clause_t):
    (type == AST_FOR_CLAUSE)? sizeof(ast_for_clause_t):
    (type == AST_WHILE_CLAUSE)? sizeof(ast_while_clause_t):
    (type == AST_DO_CLAUSE)? sizeof(ast_do_clause_t):
    (type == AST_TRY_CLAUSE)? sizeof(ast_try_clause_t):
    (type == AST_EXCEPT_CLAUSE)? sizeof(ast_except_clause_t):
    (type == AST_FINALLY_CLAUSE)? sizeof(ast_finally_clause_t):
    (size_t)-1;


    return size;
}

