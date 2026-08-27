
/*
 * This is a generated file
 */
#include <stddef.h>
#include "ast.h"
#include "common.h"

static inline size_t get_node_size(ast_type_t type);

ast_node_t* create_ast_node(ast_type_t type) {

    ast_node_t* node = _ALLOC(get_node_size(type));
    node->type = type;

    return node;
}

void destroy_ast_node(ast_node_t* node) {

    if(node != NULL) {
        _FREE(node);
    }
}

ast_node_list_t* create_ast_node_list(void) {
    return create_ptr_list();
}

void destroy_ast_node_list(ast_node_list_t* lst) {
    if(lst != NULL) {
        for(int i = 0; i < lst->len; i++)
            destroy_ast_node(lst->buffer[i]);
        destroy_ptr_list(lst);
    }
}

void append_ast_node_list(ast_node_list_t* lst, ast_node_t* node) {
    append_ptr_list(lst, (void*)node);
}

ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, int* mark) {
    return (ast_node_t*)iterate_ptr_list(lst, mark);
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

static inline size_t get_node_size(ast_type_t type) {
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

