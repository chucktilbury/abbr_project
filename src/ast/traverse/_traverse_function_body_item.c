
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

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
void _traverse_function_body_item(ast_function_body_item_t* node) {
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

