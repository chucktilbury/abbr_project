
/*
    This AST pass does nothing but traverse the tree and print relevent trace
    information if it's enabled. It is one big file because it's intended to
    be used as a template, copied and edited to actually contain useful
    functionality. The parser returns a pointer to the tree.
*/

#include "common.h"
#include "ast.h"

static inline void _traverse_module(ast_module_t* node);
static inline void _traverse_start_clause(ast_start_clause_t* node);
static inline void _traverse_module_item(ast_module_item_t* node);
static inline void _traverse_include_statement(ast_include_statement_t* node);
static inline void _traverse_import_statement(ast_import_statement_t* node);
static inline void _traverse_namespace_item(ast_namespace_item_t* node);
static inline void _traverse_global_scope_operator(ast_global_scope_operator_t* node);
static inline void _traverse_class_scope_operator(ast_class_scope_operator_t* node);
static inline void _traverse_namespace(ast_namespace_t* node);
static inline void _traverse_class_definition(ast_class_definition_t* node);
static inline void _traverse_inheritance_item(ast_inheritance_item_t* node);
static inline void _traverse_class_item(ast_class_item_t* node);
static inline void _traverse_function_declaration(ast_function_declaration_t* node);
static inline void _traverse_constructor_declaration(ast_constructor_declaration_t* node);
static inline void _traverse_destructor_declaration(ast_destructor_declaration_t* node);
static inline void _traverse_function_definition_parameters(ast_function_definition_parameters_t* node);
static inline void _traverse_function_decl_parameter(ast_function_decl_parameter_t* node);
static inline void _traverse_function_declaration_parameters(ast_function_declaration_parameters_t* node);
static inline void _traverse_type_specifier(ast_type_specifier_t* node);
static inline void _traverse_function_definition(ast_function_definition_t* node);
static inline void _traverse_constructor_definition(ast_constructor_definition_t* node);
static inline void _traverse_destructor_definition(ast_destructor_definition_t* node);
static inline void _traverse_data_declaration(ast_data_declaration_t* node);
static inline void _traverse_compound_name(ast_compound_name_t* node);
static inline void _traverse_const_value(ast_const_value_t* node);
static inline void _traverse_literal_string(ast_literal_string_t* node);
static inline void _traverse_formatted_string(ast_formatted_string_t* node);
static inline void _traverse_literal_array_definition(ast_literal_array_definition_t* node);
static inline void _traverse_literal_dict_item(ast_literal_dict_item_t* node);
static inline void _traverse_literal_dict_definition(ast_literal_dict_definition_t* node);
static inline void _traverse_primary_expression(ast_primary_expression_t* node);
static inline void _traverse_expression(ast_expression_t* node);
static inline void _traverse_compound_reference(ast_compound_reference_t* node);
static inline void _traverse_compound_reference_item(ast_compound_reference_item_t* node);
static inline void _traverse_function_reference(ast_function_reference_t* node);
static inline void _traverse_array_reference(ast_array_reference_t* node);
static inline void _traverse_array_parameters(ast_array_parameters_t* node);
static inline void _traverse_function_body_item(ast_function_body_item_t* node);
static inline void _traverse_raise_statement(ast_raise_statement_t* node);
static inline void _traverse_flow_statement(ast_flow_statement_t* node);
static inline void _traverse_loop_body_item(ast_loop_body_item_t* node);
static inline void _traverse_yield_statement(ast_yield_statement_t* node);
static inline void _traverse_loop_body(ast_loop_body_t* node);
static inline void _traverse_function_body(ast_function_body_t* node);
static inline void _traverse_assignment(ast_assignment_t* node);
static inline void _traverse_data_definition(ast_data_definition_t* node);
static inline void _traverse_return_statement(ast_return_statement_t* node);
static inline void _traverse_if_clause(ast_if_clause_t* node);
static inline void _traverse_else_clause(ast_else_clause_t* node);
static inline void _traverse_final_else_clause(ast_final_else_clause_t* node);
static inline void _traverse_for_clause(ast_for_clause_t* node);
static inline void _traverse_while_clause(ast_while_clause_t* node);
static inline void _traverse_do_clause(ast_do_clause_t* node);
static inline void _traverse_try_clause(ast_try_clause_t* node);
static inline void _traverse_except_clause(ast_except_clause_t* node);
static inline void _traverse_finally_clause(ast_finally_clause_t* node);
static inline void _traverse_exit_statement(ast_exit_statement_t* node);
static inline void _traverse_inline_statement(ast_inline_statement_t* node);
static inline void _traverse_break_statement(ast_break_statement_t* node);
static inline void _traverse_continue_statement(ast_continue_statement_t* node);
static inline void _traverse_literal_number(ast_literal_number_t* node);
static inline void _traverse_string_literal(ast_string_literal_t* node);
static inline void _traverse_literal_type(ast_literal_type_t* node);
static inline void _traverse_identifier(ast_identifier_t* node);

#define NODE_TYPE(n) ((ast_node_t*)n)->type
#define SHOW_TOKEN(t)    \
    do { \
        if((t) != NULL && verbosity >= DEFAULT_TRACE) { \
            INDENT; \
            printf("%s: ", colorize(fgCYA, aBOLD, 0, "TOKEN: ")); \
            print_token(t); \
        } \
    } while(0)

#define SHOW_TOKEN_TYPE(t)    \
    do { \
        if(verbosity >= DEFAULT_TRACE) { \
            INDENT; \
            printf("%s: %s\n", colorize(fgCYA, aBOLD, 0, "TOKEN TYPE: "), \
                token_type_to_str(t)); \
        } \
    } while(0)

#define SHOW_STRING(s)    \
    do { \
        if((s) != NULL && verbosity >= DEFAULT_TRACE) { \
            INDENT; \
            printf("%s: %s\n", colorize(fgCYA, aBOLD, 0, "STRING: "), raw_string(s)); \
        } \
    } while(0)

#define TRAVERSE_ENTER \
    do { ENTER; \
        ASSERT(node != NULL, "invalid AST node encountered in %s", __PRETTY_FUNCTION__); \
    } while(0);


/*
 *  module
 *      : module_item*
 *      | start_clause
 *      ;
 */
static inline void _traverse_module(ast_module_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL;
                ptr = iterate_ast_node_list(node->list, &mark)) {

        switch(NODE_TYPE(ptr)) {
            case AST_MODULE_ITEM:
                _traverse_module_item((ast_module_item_t*)ptr);
                break;
            case AST_START_CLAUSE:
                _traverse_start_clause((ast_start_clause_t*)ptr);
                break;
            default:
                FATAL("unknown node type");
        }
    }
    RETURN();
}

/*
 *  start_clause
 *      : 'start' function_body
 *      ;
 */
static inline void _traverse_start_clause(ast_start_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  module_item
 *      : namespace_item
 *      | include_statement
 *      | import_statement
 *      ;
 */
static inline void _traverse_module_item(ast_module_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_NAMESPACE_ITEM:
            _traverse_namespace_item((ast_namespace_item_t*)node->item);
            break;
        // There is no reason to traverse includes or imports. That is handled
        // completely by the parser.
        case AST_INCLUDE_STATEMENT:
            _traverse_include_statement((ast_include_statement_t*)node->item);
            break;
        case AST_IMPORT_STATEMENT:
            _traverse_import_statement((ast_import_statement_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

/*
 *  include_statement
 *      : 'include' string_literal
 *      ;
 */
static inline void _traverse_include_statement(ast_include_statement_t* node) {
    TRAVERSE_ENTER;

    // includes are handled during parsing. this should probably never be called.
    _traverse_string_literal(node->str);
    RETURN();
}

/*
 *  import_statement
 *      : 'import' (LITERAL_DSTR | LITERAL_SSTR)
 *      | 'import' compound_name ( ('from' (LITERAL_DSTR | LITERAL_SSTR))? ('as' IDENTIFIER)? )?
 *      ;
 */
static inline void _traverse_import_statement(ast_import_statement_t* node) {
    TRAVERSE_ENTER;

    // imports are handled during parsing. this should probably never be called.
    _traverse_compound_name(node->compound_name);
    if(node->str != NULL)
        _traverse_string_literal(node->str);
    _traverse_identifier(node->identifier);
    RETURN();
}

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
static inline void _traverse_namespace_item(ast_namespace_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_GLOBAL_SCOPE_OPERATOR:
            _traverse_global_scope_operator((ast_global_scope_operator_t*)node->item);
            break;
        case AST_CLASS_DEFINITION:
            _traverse_class_definition((ast_class_definition_t*)node->item);
            break;
        case AST_FUNCTION_DEFINITION:
            _traverse_function_definition((ast_function_definition_t*)node->item);
            break;
        case AST_CONSTRUCTOR_DEFINITION:
            _traverse_constructor_definition((ast_constructor_definition_t*)node->item);
            break;
        case AST_DESTRUCTOR_DEFINITION:
            _traverse_destructor_definition((ast_destructor_definition_t*)node->item);
            break;
        case AST_NAMESPACE:
            _traverse_namespace((ast_namespace_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

/*
 *  global_scope_operator
 *      : 'public'
 *      | 'private'
 *      ;
 */
static inline void _traverse_global_scope_operator(ast_global_scope_operator_t* node) {
    TRAVERSE_ENTER;

    SHOW_TOKEN_TYPE(node->tok);

    RETURN();
}

/*
 *  class_scope_operator
 *      : 'public'
 *      | 'private'
 *      | 'protected'
 *      ;
 */
static inline void _traverse_class_scope_operator(ast_class_scope_operator_t* node) {
    TRAVERSE_ENTER;

    SHOW_TOKEN_TYPE(node->tok);

    RETURN();
}

/*
 *  namespace
 *      : 'namespace' IDENTIFIER '{' namespace_item* '}'
 *      ;
 */
static inline void _traverse_namespace(ast_namespace_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
               ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_namespace_item((ast_namespace_item_t*)ptr);
    }

    RETURN();
}

/*
 *  class_definition
 *      : 'class' IDENTIFIER ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
 *      ;
 */
static inline void _traverse_class_definition(ast_class_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->i_list, &mark);
               ptr != NULL; ptr = iterate_ast_node_list(node->i_list, &mark)) {
        _traverse_inheritance_item((ast_inheritance_item_t*)ptr);
    }

    mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->c_list, &mark);
               ptr != NULL; ptr = iterate_ast_node_list(node->c_list, &mark)) {
        _traverse_class_item((ast_class_item_t*)ptr);
    }

    RETURN();
}

/*
 *  inheritance_item
 *      : class_scope_operator? compound_name
 *      ;
 */
static inline void _traverse_inheritance_item(ast_inheritance_item_t* node) {
    TRAVERSE_ENTER;

    if(node->class_scope_operator != NULL)
        _traverse_class_scope_operator(node->class_scope_operator);

    _traverse_compound_name(node->compound_name);

    RETURN();
}

/*
 *  class_item
 *      : class_scope_operator
 *      | function_declaration
 *      | data_declaration
 *      | constructor_declaration
 *      | destructor_declaration
 *      ;
 */
static inline void _traverse_class_item(ast_class_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_CLASS_SCOPE_OPERATOR:
            _traverse_class_scope_operator((ast_class_scope_operator_t*)node->item);
            break;
        case AST_FUNCTION_DECLARATION:
            _traverse_function_declaration((ast_function_declaration_t*)node->item);
            break;
        case AST_DATA_DECLARATION:
            _traverse_data_declaration((ast_data_declaration_t*)node->item);
            break;
        case AST_CONSTRUCTOR_DECLARATION:
            _traverse_constructor_declaration((ast_constructor_declaration_t*)node->item);
            break;
        case AST_DESTRUCTOR_DECLARATION:
            _traverse_destructor_declaration((ast_destructor_declaration_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

/*
 *  function_declaration
 *      : type_specifier IDENTIFIER function_declaration_parameters function_body?
 *      ;
 */
static inline void _traverse_function_declaration(ast_function_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);
    _traverse_type_specifier(node->type_specifier);
    _traverse_function_declaration_parameters(node->function_declaration_parameters);

    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}

/*
 *  constructor_declaration
 *      : 'create' function_declaration_parameters function_body?
 *      ;
 */
static inline void _traverse_constructor_declaration(ast_constructor_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_declaration_parameters(node->function_declaration_parameters);
    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}

/*
 *  destructor_declaration
 *      : 'destroy' function_body?
 *      ;
 */
static inline void _traverse_destructor_declaration(ast_destructor_declaration_t* node) {
    TRAVERSE_ENTER;

    if(node->func_body != NULL)
        _traverse_function_body(node->func_body);

    RETURN();
}

/*
 *  function_definition_parameters
 *      : '(' (data_declaration (',' data_declaration)*)? ')'
 *      ;
 */
static inline void _traverse_function_definition_parameters(ast_function_definition_parameters_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->data_declaration, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->data_declaration, &mark)) {
        _traverse_data_declaration((ast_data_declaration_t*)ptr);
    }

    RETURN();
}

/*
 *  function_decl_parameter
 *      : type_specifier (IDENTIFIER)?
 *      ;
 */
static inline void _traverse_function_decl_parameter(ast_function_decl_parameter_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);

    _traverse_identifier(node->identifier);

    RETURN();
}

/*
 *  function_declaration_parameters
 *      : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
 *      ;
 */
static inline void _traverse_function_declaration_parameters(ast_function_declaration_parameters_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_function_decl_parameter((ast_function_decl_parameter_t*)ptr);
    }
    RETURN();
}

/*
 *  type_specifier
 *      : literal_type
 *      | compound_name
 *      ;
 */
static inline void _traverse_type_specifier(ast_type_specifier_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_COMPOUND_NAME:
            _traverse_compound_name((ast_compound_name_t*)node->item);
            break;
        case AST_LITERAL_TYPE:
            _traverse_literal_type((ast_literal_type_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

/*
 *  function_definition
 *      : type_specifier IDENTIFIER '.' IDENTIFIER function_definition_parameters function_body
 *      ;
 */
static inline void _traverse_function_definition(ast_function_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);
    _traverse_identifier(node->group);
    _traverse_identifier(node->name);
    _traverse_function_definition_parameters(node->function_definition_parameters);
    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  constructor_definition
 *      : IDENTIFIER '.' 'create' function_definition_parameters function_body
 *      ;
 */
static inline void _traverse_constructor_definition(ast_constructor_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->group);
    _traverse_function_definition_parameters(node->function_definition_parameters);
    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  destructor_definition
 *      : IDENTIFIER '.' 'destroy' function_body
 *      ;
 */
static inline void _traverse_destructor_definition(ast_destructor_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->group);
    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  data_declaration
 *      : type_specifier IDENTIFIER ( '=' const_value )?
 *      ;
 */
static inline void _traverse_data_declaration(ast_data_declaration_t* node) {
    TRAVERSE_ENTER;

    _traverse_type_specifier(node->type_specifier);
    _traverse_identifier(node->identifier);

    if(node->const_value != NULL)
        _traverse_const_value(node->const_value);

    RETURN();
}

/*
 *  compound_name
 *      : IDENTIFIER ('.' IDENTIFIER)*
 *      ;
 */
static inline void _traverse_compound_name(ast_compound_name_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_identifier((ast_identifier_t*)ptr);
    }

    RETURN();
}

/*
 *  const_value
 *      : literal_number
 *      | string_literal
 *      | literal_array_definition
 *      | literal_dict_definition
 *      ;
 */
static inline void _traverse_const_value(ast_const_value_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_LITERAL_ARRAY_DEFINITION:
            _traverse_literal_array_definition(((ast_literal_array_definition_t*)node->item));
            break;
        case AST_LITERAL_DICT_DEFINITION:
            _traverse_literal_dict_definition(((ast_literal_dict_definition_t*)node->item));
            break;
        case AST_LITERAL_NUMBER:
            _traverse_literal_number(((ast_literal_number_t*)node->item));
            break;
        case AST_STRING_LITERAL:
            _traverse_string_literal(((ast_string_literal_t*)node->item));
            break;
        default:
            FATAL("invalid node type");
    }

    RETURN();
}

/*
 *  literal_string
 *      : LITERAL_SSTR
 *      | formatted_string
 *      ;
 */
static inline void _traverse_literal_string(ast_literal_string_t* node) {
    TRAVERSE_ENTER;

    if(node->literal_str != NULL) {
        SHOW_STRING(node->literal_str);
    }
    else
        _traverse_formatted_string(node->formatted_string);

    RETURN();
}

/*
 *  formatted_string
 *      : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
 *      ;
 */
static inline void _traverse_formatted_string(ast_formatted_string_t* node) {
    TRAVERSE_ENTER;

    SHOW_STRING(node->literal_str);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_expression((ast_expression_t*)ptr);
    }

    RETURN();
}

/*
 *  literal_array_definition
 *      : '[' const_value (',' const_value)* ']'
 *      ;
 */
static inline void _traverse_literal_array_definition(ast_literal_array_definition_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->const_value, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->const_value, &mark)) {
        _traverse_const_value((ast_const_value_t*)ptr);
    }

    RETURN();
}

/*
 *  literal_dict_item
 *      : string_literal ':' const_value
 *      ;
 */
static inline void _traverse_literal_dict_item(ast_literal_dict_item_t* node) {
    TRAVERSE_ENTER;

    _traverse_string_literal(node->literal_str);
    _traverse_const_value(node->const_value);

    RETURN();
}

/*
 *  literal_dict_definition
 *      : '[' literal_dict_item (',' literal_dict_item)* ']'
 *      ;
 */
static inline void _traverse_literal_dict_definition(ast_literal_dict_definition_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->literal_dict_item, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->literal_dict_item, &mark)) {
        _traverse_literal_dict_item((ast_literal_dict_item_t*)ptr);
    }

    RETURN();
}

/*
 *  primary_expression
 *      : literal_number
 *      | literal_string
 *      | compound_reference
 *      ;
 */
static inline void _traverse_primary_expression(ast_primary_expression_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->value)) {
        case AST_LITERAL_STRING:
            _traverse_literal_string((ast_literal_string_t*)node->value);
            break;
        case AST_LITERAL_NUMBER:
            _traverse_literal_number((ast_literal_number_t*)node->value);
            break;
        case AST_COMPOUND_REFERENCE:
            _traverse_compound_reference((ast_compound_reference_t*)node->value);
            break;
        default:
            FATAL("unknown node type");
    }

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
static inline void _traverse_expression(ast_expression_t* node) {
    TRAVERSE_ENTER;

    // TBD-- this will certainly change
    (void)node;

    RETURN();
}

/*
 *  compound_reference
 *      : compound_reference_item ('.' compound_reference_item)*
 *      ;
 */
static inline void _traverse_compound_reference(ast_compound_reference_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->list, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->list, &mark)) {
        _traverse_compound_reference_item((ast_compound_reference_item_t*)ptr);
    }

    RETURN();
}

/*
 *  compound_reference_item
 *      : IDENTIFIER
 *      | function_reference
 *      | array_reference
 *      ;
 */
static inline void _traverse_compound_reference_item(ast_compound_reference_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_FUNCTION_REFERENCE:
            _traverse_function_reference((ast_function_reference_t*)node->item);
            break;
        case AST_ARRAY_REFERENCE:
            _traverse_array_reference((ast_array_reference_t*)node->item);
            break;
        case AST_IDENTIFIER:
            _traverse_identifier((ast_identifier_t*)node->item);
            break;
        default:
            FATAL("unknown node type");
    }

    RETURN();
}

/*
 *  function_reference
 *      : IDENTIFIER '(' expression (',' expression)* ')'
 *      ;
 */
static inline void _traverse_function_reference(ast_function_reference_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->expr, &mark);
            ptr != NULL; ptr = iterate_ast_node_list(node->expr, &mark)) {
        _traverse_expression((ast_expression_t*)ptr);
    }

    RETURN();
}

/*
 *  array_reference
 *      : IDENTIFIER array_parameters (array_parameters)*
 *      ;
 */
static inline void _traverse_array_reference(ast_array_reference_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->array_parameters, &mark);
            ptr != NULL; ptr = iterate_ast_node_list(node->array_parameters, &mark)) {
        _traverse_array_parameters((ast_array_parameters_t*)ptr);
    }

    RETURN();
}

/*
 *  array_parameters
 *      : '[' (array_parameters | expression) ']'
 *      ;
 */
static inline void _traverse_array_parameters(ast_array_parameters_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_ARRAY_PARAMETERS:
            _traverse_array_parameters((ast_array_parameters_t*)node->item);
            break;
        case AST_EXPRESSION:
            _traverse_expression((ast_expression_t*)node->item);
            break;
        default:
            FATAL("invalid node type");
    }

    RETURN();
}

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
 *      | function_body
 *      ;
 */
static inline void _traverse_function_body_item(ast_function_body_item_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_COMPOUND_REFERENCE:
            _traverse_compound_reference((ast_compound_reference_t*)node->item);
            break;
        case AST_ASSIGNMENT:
            _traverse_assignment((ast_assignment_t*)node->item);
            break;
        case AST_DATA_DEFINITION:
            _traverse_data_definition((ast_data_definition_t*)node->item);
            break;
        case AST_FLOW_STATEMENT:
            _traverse_flow_statement((ast_flow_statement_t*)node->item);
            break;
        case AST_EXIT_STATEMENT:
            _traverse_exit_statement((ast_exit_statement_t*)node->item);
            break;
        case AST_RAISE_STATEMENT:
            _traverse_raise_statement((ast_raise_statement_t*)node->item);
            break;
        case AST_RETURN_STATEMENT:
            _traverse_return_statement((ast_return_statement_t*)node->item);
            break;
        case AST_INLINE_STATEMENT:
            _traverse_inline_statement((ast_inline_statement_t*)node->item);
            break;
        case AST_FUNCTION_BODY:
            _traverse_function_body((ast_function_body_t*)node->item);
            break;
        default:
            FATAL("invalid node type");
    }

    RETURN();
}

/*
 *  raise_statement
 *      : 'raise' '(' compound_name ')'
 *      ;
 */
static inline void _traverse_raise_statement(ast_raise_statement_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_name(node->compound_name);

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
static inline void _traverse_flow_statement(ast_flow_statement_t* node) {
    TRAVERSE_ENTER;

    switch(NODE_TYPE(node->item)) {
        case AST_IF_CLAUSE:
            _traverse_if_clause((ast_if_clause_t*)node->item);
            break;
        case AST_FOR_CLAUSE:
            _traverse_for_clause((ast_for_clause_t*)node->item);
            break;
        case AST_WHILE_CLAUSE:
            _traverse_while_clause((ast_while_clause_t*)node->item);
            break;
        case AST_DO_CLAUSE:
            _traverse_do_clause((ast_do_clause_t*)node->item);
            break;
        case AST_TRY_CLAUSE:
            _traverse_try_clause((ast_try_clause_t*)node->item);
            break;
        default:
            FATAL("invalid node type");

    }

    RETURN();
}

/*
 *  loop_body_item
 *      : function_body_item
 *      | yield_statement
 *      | break_statement
 *      | continue_statement
 *      | loop_body
 *      ;
 */
static inline void _traverse_loop_body_item(ast_loop_body_item_t* node) {
    TRAVERSE_ENTER;

    if(node->item != NULL) {
        switch(NODE_TYPE(node->item)) {
            case AST_FUNCTION_BODY_ITEM:
                _traverse_function_body_item((ast_function_body_item_t*)node->item);
                break;
            case AST_YIELD_STATEMENT:
                _traverse_yield_statement((ast_yield_statement_t*)node->item);
                break;
            case AST_BREAK_STATEMENT:
                _traverse_break_statement((ast_break_statement_t*)node->item);
                break;
            case AST_CONTINUE_STATEMENT:
                _traverse_continue_statement((ast_continue_statement_t*)node->item);
                break;
            case AST_LOOP_BODY:
                _traverse_loop_body((ast_loop_body_t*)node->item);
                break;
            default:
                FATAL("invalid node type");
        }
    }

    RETURN();
}

/*
 *  yield_statement
 *      : 'yield' '(' expression ')'
 *      ;
 */
static inline void _traverse_yield_statement(ast_yield_statement_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);

    RETURN();
}

/*
 *  loop_body
 *      : '{' loop_body_item* '}'
 *      ;
 */
static inline void _traverse_loop_body(ast_loop_body_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_loop_body_item((ast_loop_body_item_t*)ptr);
    }

    RETURN();
}

/*
 *  function_body
 *      : '{' function_body_item+ '}'
 *      ;
 */
static inline void _traverse_function_body(ast_function_body_t* node) {
    TRAVERSE_ENTER;

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->item, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->item, &mark)) {
        _traverse_function_body_item((ast_function_body_item_t*)ptr);
    }

    RETURN();
}

/*
 *  assignment
 *      : compound_reference '=' expression
 *      ;
 */
static inline void _traverse_assignment(ast_assignment_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_reference(node->compound_reference);
    _traverse_expression(node->expression);

    RETURN();
}

/*
 *  data_definition
 *      : type_specifier IDENTIFIER ( '=' expression )?
 *      ;
 */
static inline void _traverse_data_definition(ast_data_definition_t* node) {
    TRAVERSE_ENTER;

    _traverse_identifier(node->identifier);
    _traverse_type_specifier(node->type_specifier);
    if(node->expression != NULL)
        _traverse_expression(node->expression);

    RETURN();
}

/*
 *  return_statement
 *      : 'return' ( '(' expression? ')' )?
 *      ;
 */
static inline void _traverse_return_statement(ast_return_statement_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL)
        _traverse_expression(node->expr);

    RETURN();
}

/*
 *  if_clause
 *      : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
 *      ;
 */
static inline void _traverse_if_clause(ast_if_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);
    _traverse_function_body(node->function_body);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->else_clause, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->else_clause, &mark)) {
        _traverse_else_clause((ast_else_clause_t*)ptr);
    }

    if(node->final_else_clause != NULL) {
        _traverse_final_else_clause(node->final_else_clause);
    }

    RETURN();
}

/*
 *  else_clause
 *      : 'else' '(' expression ')' function_body
 *      ;
 */
static inline void _traverse_else_clause(ast_else_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_expression(node->expr);
    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  final_else_clause
 *      : 'else' ( '(' ')' )? function_body
 *      ;
 */
static inline void _traverse_final_else_clause(ast_final_else_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  for_clause
 *      : 'for' ( '(' ( expression ('as' (type_specifier)? IDENTIFIER)? )? ')' )? loop_body
 *      ;
 */
static inline void _traverse_for_clause(ast_for_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->identifier != NULL) {
        _traverse_identifier(node->identifier);
    }

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    if(node->type_specifier != NULL) {
        _traverse_type_specifier(node->type_specifier);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}

/*
 *  while_clause
 *      : 'while' ( '(' expression? ')' )? loop_body
 *      ;
 */
static inline void _traverse_while_clause(ast_while_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}

/*
 *  do_clause
 *      : 'do' loop_body 'while' ( '(' expression? ')' )?
 *      ;
 */
static inline void _traverse_do_clause(ast_do_clause_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL) {
        _traverse_expression(node->expr);
    }

    _traverse_loop_body(node->loop_body);

    RETURN();
}

/*
 *  try_clause
 *      : 'try' function_body except_clause+ finally_clause?
 *      ;
 */
static inline void _traverse_try_clause(ast_try_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    int mark = 0;
    for(ast_node_t* ptr = iterate_ast_node_list(node->except_clause, &mark);
                ptr != NULL; ptr = iterate_ast_node_list(node->except_clause, &mark)) {
        _traverse_except_clause((ast_except_clause_t*)ptr);
    }

    if(node->finally_clause != NULL)
        _traverse_finally_clause(node->finally_clause);

    RETURN();
}

/*
 *  except_clause
 *      : 'except' '(' compound_name ('as' IDENTIFIER)? ')' function_body
 *      ;
 */
static inline void _traverse_except_clause(ast_except_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_compound_name(node->compound_name);

    if(node->identifier != NULL) {
        _traverse_identifier(node->identifier);
    }

    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  finally_clause
 *      : 'finally' function_body
 *      ;
 */
static inline void _traverse_finally_clause(ast_finally_clause_t* node) {
    TRAVERSE_ENTER;

    _traverse_function_body(node->function_body);

    RETURN();
}

/*
 *  exit_statement
 *      : 'exit' '(' expression? ')'
 *      ;
 */
static inline void _traverse_exit_statement(ast_exit_statement_t* node) {
    TRAVERSE_ENTER;

    if(node->expr != NULL)
        _traverse_expression(node->expr);

    RETURN();
}

/*
 * Note that this is returned by the scanner as a TOK_INLINE token.
 *
 *  inline_statement
 *      : 'inline' '{' RAW_TEXT '}'
 */
static inline void _traverse_inline_statement(ast_inline_statement_t* node) {
    TRAVERSE_ENTER;

    SHOW_STRING(node->str);

    RETURN();
}

/*
 *  break_statement
 *      : 'break'
 *      ;
 */
static inline void _traverse_break_statement(ast_break_statement_t* node) {
    TRAVERSE_ENTER;
    (void)node;
    RETURN();
}

/*
 *  continue_statement
 *      : 'continue'
 *      ;
 */
static inline void _traverse_continue_statement(ast_continue_statement_t* node) {
    TRAVERSE_ENTER;
    (void)node;
    RETURN();
}

/*
 *  string_literal
 *      : LITERAL_DSTR
 *      | LITERAL_SSTR
 *      ;
 */
static inline void _traverse_string_literal(ast_string_literal_t* node) {
    TRAVERSE_ENTER;
    SHOW_STRING(node->str);
    RETURN();
}

/*
 *  literal_number
 *      : LITERAL_INT
 *      | LITERAL_UINT
 *      | LITERAL_FLOAT
 *      | LITERAL_BOOL
 *      ;
 */
static inline void _traverse_literal_number(ast_literal_number_t* node) {
    TRAVERSE_ENTER;
    SHOW_TOKEN_TYPE(node->value_type);
    // not showing the union with the actual values. This is set by the parser.
    RETURN();
}

/*
 *  literal_type_specifier
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
static inline void _traverse_literal_type(ast_literal_type_t* node) {
    TRAVERSE_ENTER;
    SHOW_TOKEN_TYPE(node->type);
    RETURN();
}

/*
 *  identifier
 *      : IDENTIFIER
 *      ;
 */
static inline void _traverse_identifier(ast_identifier_t* node) {
    TRAVERSE_ENTER;
    SHOW_STRING(node->name);
    RETURN();
}

/*
 * Main entry point for AST traverse
 */
void traverse_ast(ast_node_t* node) {
    TRAVERSE_ENTER;
    if(node == NULL)
        FATAL("invalid node");
    _traverse_module((ast_module_t*)node);
    RETURN();
}

