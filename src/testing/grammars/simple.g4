
grammar simple;

module
    : module_body EOF
    ;

module_body
    : module_item*
    | start_statement
    ;

module_item
    : namespace_item
    | import_statement
    | include_statement
    ;

scope_operator
    : 'private'
    | 'public'
    ;

namespace_definition
    : 'namespace' IDENTIFIER '{' namespace_item+ '}'
    ;

namespace_item
    : class_definition
    | method_definition
    | namespace_definition
    | scope_operator
    ;

compound_name
    : IDENTIFIER ('.' IDENTIFIER)*
    ;

class_definition
    : 'class' IDENTIFIER ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
    ;

class_scope_operator
    : 'protected'
    | scope_operator
    ;

inheritance_item
    : compound_name IDENTIFIER
    | class_scope_operator compound_name IDENTIFIER
    ;

class_item
    : class_scope_operator
    | data_declaration
    | method_declaration
    | method_definition
    ;

type_name
    : 'integer' | 'int'
    | 'unsigned'
    | 'float'
    | 'string'
    | 'bool'
    | 'array'
    | 'dict'
    | 'nothing'
    | compound_name
    ;

data_declaration
    : type_name IDENTIFIER ('=' expression)?
    ;

method_decl_parm
    : type_name
    | data_declaration
    ;

method_definition
    : IDENTIFIER '.' 'construct' '(' (method_decl_parm (',' method_decl_parm)*)? ')' '{' function_body+ '}'
    | IDENTIFIER '.' 'destroy' '{' function_body+ '}'
    | type_name IDENTIFIER '.' IDENTIFIER '(' (method_decl_parm (',' method_decl_parm)*)? ')' '{' function_body+ '}'
    ;

method_declaration
    : 'construct' '(' (method_decl_parm (',' method_decl_parm)*)? ')'
    | type_name IDENTIFIER '(' (method_decl_parm (',' method_decl_parm)*)? ')'
    ;

literal_unprocessed_string
    : LITERAL_SSTR
    | LITERAL_DSTR
    ;

import_statement
    : 'import' (IDENTIFIER 'from')? literal_unprocessed_string ('as' IDENTIFIER)?
    ;

include_statement
    : 'include' literal_unprocessed_string
    ;

start_statement
    : 'start' '{' function_body+ '}'
    ;

literal_string
    : LITERAL_SSTR
    | formatted_string
    ;

formatted_string
    : LITERAL_DSTR ( '(' (expression (',' expression)*)? ')' )?
    ;

compound_ref_element
    : IDENTIFIER
    | array_ref
    | function_ref
    ;

array_ref
    : IDENTIFIER '[' expression ']' ('[' expression ']')*
    ;

function_ref
    : IDENTIFIER '(' (expression (',' expression)*)? ')'
    ;

compound_reference
    : compound_ref_element ('.' compound_ref_element)*
    ;

primary_expr
    : LITERAL_INT
    | LITERAL_UNS
    | LITERAL_FLOAT
    | literal_string
    | compound_reference
    | '(' expression ')'
    ;

expression
    : expression ('*' | '/' | '%') expression
    | expression ('+' | '-') expression
    | expression ('<' | '>' | '<=' | '>=' | 'lt' | 'gt' | 'lte' | 'gte') expression
    | expression ('==' | '!=' | 'equ' | 'neq' ) expression
    | expression ('&&' | 'and') expression
    | expression ('||' | 'or') expression
    | ('!' | 'not') expression
    | primary_expr
    ;

function_body
    : print_statement
    | exit_statement
    | compound_reference
    | data_declaration
    | assignment
    | if_clause
    | for_clause
    | while_clause
    | do_clause
    | try_clause
    ;

print_statement
    : 'print' ( '(' literal_string? ')')?
    ;

exit_statement
    : 'exit' '(' expression ')'
    ;

assignment
    : compound_reference '=' expression
    | compound_reference '+=' expression
    | compound_reference '-=' expression
    | compound_reference '*=' expression
    | compound_reference '/=' expression
    ;

if_clause
    : 'if' '(' expression ')' '{' function_body+ '}' else_clause* final_else?
    ;

else_clause
    : 'else' '(' expression ')' '{' function_body+ '}'
    ;

final_else
    : 'else' ('(' ')')? '{' function_body+ '}'
    ;

for_clause
    : 'for' ('(' (expression ('as' IDENTIFIER)?)? ')')? '{' function_body+ '}'
    ;

while_clause
    : 'while' ('(' expression? ')')? '{' loop_body+ '}'
    ;

do_clause
    : 'do' '{' loop_body+ '}' 'while' ('(' expression? ')')?
    ;

try_clause
    : 'try' '{' function_body+ '}' except_clause+
    ;

except_clause
    : 'except' '(' compound_reference ('as' IDENTIFIER)? ')' '{' function_body+ '}'
    ;

loop_body
    : function_body
    | 'break'
    | 'continue'
    | 'yield'
    ;

IDENTIFIER:     [a-z_A-Z][a-zA-Z_0-9]* ;
/*LITERAL_INT:    ([+-]?[1-9][0-9]+)|'0';*/
LITERAL_INT:    [0-9]+;
LITERAL_UNS:    '0'[xX][0-9A-Fa-f]+;
LITERAL_FLOAT:  [+-]?('0'|[1-9][0-9]+)'.'[0-9]+([eE][+-]?[0-9]+)?;
LITERAL_SSTR:   '\'' .*? '\'';
LITERAL_DSTR:   '"' .*? '"';
COMMENT:        '/*' .*? '*/' -> channel (HIDDEN);
LINE_COMMENT:   '//' ~[\r\n]* -> channel (HIDDEN);
WS:             [ \r\n\t] + -> channel (HIDDEN);
