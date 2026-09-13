
#include "ast.h"
#include "ast_struct.h"
#include "traverse.h"

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
