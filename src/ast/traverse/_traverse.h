#ifndef __TRAVERSE_H_
#define __TRAVERSE_H_

#include "ast_struct.h"

void _traverse_module(ast_module_t* node);
void _traverse_start_clause(ast_start_clause_t* node);
void _traverse_module_item(ast_module_item_t* node);
void _traverse_include_statement(ast_include_statement_t* node);
void _traverse_import_statement(ast_import_statement_t* node);
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
void _traverse_type_specifier(ast_type_specifier_t* node);
void _traverse_function_definition(ast_function_definition_t* node);
void _traverse_constructor_definition(ast_constructor_definition_t* node);
void _traverse_destructor_definition(ast_destructor_definition_t* node);
void _traverse_data_declaration(ast_data_declaration_t* node);
void _traverse_compound_name(ast_compound_name_t* node);
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
void _traverse_raise_statement(ast_raise_statement_t* node);
void _traverse_flow_statement(ast_flow_statement_t* node);
void _traverse_loop_body_item(ast_loop_body_item_t* node);
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
void _traverse_inline_statement(ast_inline_statement_t* node);
void _traverse_break_statement(ast_break_statement_t* node);
void _traverse_continue_statement(ast_continue_statement_t* node);
void _traverse_literal_number(ast_literal_number_t* node);
void _traverse_string_literal(ast_string_literal_t* node);
void _traverse_literal_type(ast_literal_type_t* node);
void _traverse_identifier(ast_identifier_t* node);

#define NODE_TYPE(n) ((ast_node_t*)n)->type
#define SHOW_TOKEN(t)                                             \
    do {                                                          \
        if((t) != NULL && verbosity >= DEFAULT_TRACE) {           \
            INDENT;                                               \
            printf("%s: ", colorize(fgCYA, aBOLD, 0, "TOKEN: ")); \
            print_token(t);                                       \
        }                                                         \
    } while(0)

#define SHOW_TOKEN_TYPE(t)                                                \
    do {                                                                  \
        if(verbosity >= DEFAULT_TRACE) {                                  \
            INDENT;                                                       \
            printf("%s: %s\n", colorize(fgCYA, aBOLD, 0, "TOKEN TYPE: "), \
                   token_type_to_str(t));                                 \
        }                                                                 \
    } while(0)

#define SHOW_STRING(s)                                                                \
    do {                                                                              \
        if((s) != NULL && verbosity >= DEFAULT_TRACE) {                               \
            INDENT;                                                                   \
            printf("%s: %s\n", colorize(fgCYA, aBOLD, 0, "STRING: "), raw_string(s)); \
        }                                                                             \
    } while(0)

#define TRAVERSE_ENTER                                                                   \
    do {                                                                                 \
        ENTER;                                                                           \
        ASSERT(node != NULL, "invalid AST node encountered in %s", __PRETTY_FUNCTION__); \
    } while(0);


#endif /* __TRAVERSE_H_ */
