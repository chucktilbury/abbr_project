
/*
 * This is a generated file
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include "common.h"
#include "ast.h"

typedef enum {
    PMODE_NORMAL,
    PMODE_INCLUDE,
    PMODE_IMPORT,
} parser_mode_t;

typedef enum {
    PSCOPE_PRIVATE,
    PSCOPE_PUBLIC,
    PSCOPE_PROTECTED,
} parser_scope_t;

typedef enum {
    START_STATE,
    RETURN_MATCH,
    RETURN_NO_MATCH,
    RETURN_ERROR,
} parser_state_t;

typedef struct _parser_state_t {
    int_list_t* mode_stack;
    int_list_t* scope_stack;
    int errors;
    int warnings;
} parser_context_t;

ast_node_t* parse(void);
parser_context_t* create_parser_context(void);
void push_parser_scope(parser_context_t* context, parser_scope_t scope);
void pop_parser_scope(parser_context_t* context);
parser_scope_t peek_parser_scope(parser_context_t* context);
void push_parser_mode(parser_context_t* context, parser_mode_t mode);
void pop_parser_mode(parser_context_t* context);
parser_mode_t peek_parser_mode(parser_context_t* context);
void recover_parser_error(parser_context_t* context);

void parser_error(parser_context_t* context, const char* fmt, ...);
void parser_warning(parser_context_t* context, const char* fmt, ...);


ast_module_t* _parse_module(parser_context_t* context);
ast_start_clause_t* _parse_start_clause(parser_context_t* context);
ast_module_item_t* _parse_module_item(parser_context_t* context);
ast_include_statement_t* _parse_include_statement(parser_context_t* context);
ast_import_statement_t* _parse_import_statement(parser_context_t* context);
ast_namespace_item_t* _parse_namespace_item(parser_context_t* context);
ast_scope_operator_t* _parse_scope_operator(parser_context_t* context);
ast_class_scope_operator_t* _parse_class_scope_operator(parser_context_t* context);
ast_namespace_t* _parse_namespace(parser_context_t* context);
ast_class_definition_t* _parse_class_definition(parser_context_t* context);
ast_inheritance_item_t* _parse_inheritance_item(parser_context_t* context);
ast_class_item_t* _parse_class_item(parser_context_t* context);
ast_function_declaration_t* _parse_function_declaration(parser_context_t* context);
ast_constructor_declaration_t* _parse_constructor_declaration(parser_context_t* context);
ast_destructor_declaration_t* _parse_destructor_declaration(parser_context_t* context);
ast_function_definition_parameters_t* _parse_function_definition_parameters(parser_context_t* context);
ast_function_decl_parameter_t* _parse_function_decl_parameter(parser_context_t* context);
ast_function_declaration_parameters_t* _parse_function_declaration_parameters(parser_context_t* context);
ast_type_specifier_t* _parse_type_specifier(parser_context_t* context);
ast_function_definition_t* _parse_function_definition(parser_context_t* context);
ast_constructor_definition_t* _parse_constructor_definition(parser_context_t* context);
ast_destructor_definition_t* _parse_destructor_definition(parser_context_t* context);
ast_data_declaration_t* _parse_data_declaration(parser_context_t* context);
ast_compound_name_t* _parse_compound_name(parser_context_t* context);
ast_const_value_t* _parse_const_value(parser_context_t* context);
ast_literal_string_t* _parse_literal_string(parser_context_t* context);
ast_formatted_string_t* _parse_formatted_string(parser_context_t* context);
ast_literal_array_definition_t* _parse_literal_array_definition(parser_context_t* context);
ast_literal_dict_item_t* _parse_literal_dict_item(parser_context_t* context);
ast_literal_dict_definition_t* _parse_literal_dict_definition(parser_context_t* context);
ast_primary_expression_t* _parse_primary_expression(parser_context_t* context);
ast_expression_t* _parse_expression(parser_context_t* context);
ast_compound_reference_t* _parse_compound_reference(parser_context_t* context);
ast_compound_reference_item_t* _parse_compound_reference_item(parser_context_t* context);
ast_function_reference_t* _parse_function_reference(parser_context_t* context);
ast_array_reference_t* _parse_array_reference(parser_context_t* context);
ast_array_parameters_t* _parse_array_parameters(parser_context_t* context);
ast_function_body_item_t* _parse_function_body_item(parser_context_t* context);
ast_raise_statement_t* _parse_raise_statement(parser_context_t* context);
ast_flow_statement_t* _parse_flow_statement(parser_context_t* context);
ast_loop_body_item_t* _parse_loop_body_item(parser_context_t* context);
ast_yield_statement_t* _parse_yield_statement(parser_context_t* context);
ast_loop_body_t* _parse_loop_body(parser_context_t* context);
ast_function_body_t* _parse_function_body(parser_context_t* context);
ast_assignment_t* _parse_assignment(parser_context_t* context);
ast_data_definition_t* _parse_data_definition(parser_context_t* context);
ast_return_statement_t* _parse_return_statement(parser_context_t* context);
ast_if_clause_t* _parse_if_clause(parser_context_t* context);
ast_else_clause_t* _parse_else_clause(parser_context_t* context);
ast_final_else_clause_t* _parse_final_else_clause(parser_context_t* context);
ast_for_clause_t* _parse_for_clause(parser_context_t* context);
ast_while_clause_t* _parse_while_clause(parser_context_t* context);
ast_do_clause_t* _parse_do_clause(parser_context_t* context);
ast_try_clause_t* _parse_try_clause(parser_context_t* context);
ast_except_clause_t* _parse_except_clause(parser_context_t* context);
ast_finally_clause_t* _parse_finally_clause(parser_context_t* context);

#ifdef USE_TRACE
#define TRACE_STATE \
    do { \
        if(verbosity >= DEFAULT_TRACE) { \
            INDENT; \
            printf("%s: %d\n", colorize(fgCYA, aBOLD, 0, "STATE: "), state); \
        } \
    } while(0)
#else
#define TRACE_STATE
#endif

#endif /* _PARSER_H_ */


