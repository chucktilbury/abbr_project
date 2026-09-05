# Abbr
This is the **Abbr** abbreviated programming language. The **Abbr** language is a synthesis of C, C++, and Python. I have taken all of the features that I like from them and left out the ones that I don't like to create a complete and useful way to develop object oriented software quickly and easily from a platform that is easy and fun to use.

Full featured application development language that uses the C programming language as the intermediate representation.

## Features

* Garbage collection
* Strong type system
* Name spaces
* Class based, in that no code or data can appear outside of a class
* Include and Import are different concepts
* Strings, arrays, and hash tables are native types
* Comparison and arithmetic expressions are syntactically different things
* The dot operator **'.'** specifies a path to an object
* Overloaded functions
* Exceptions (try/except/raise)
* Support for arbitrary external libraries
* Everything is an object, but native types cannot be polymorphic
* All of the functions found in libc and libm are supported by the runtime library.
* Formatted strings
* Multi-pass compiler. No need to define before access.

## Omitted Features

* Pointers
* Explicit memory allocation
* Nothing is "global" with a notion of a "root" name space
* Inline code

## Overview

The syntax is similar to C/C++ but without some of the crust that is has accumulated.

* There is no **'->'** operator
* No **';'** after statements
* No **'virtual'** keyword
* No need to explicitly initialize members.
* No operator overloads

## Syntax Example

```
// This is a comment
; This is a comment
/*
    This is a comment
*/

// import copies the symbols so they can be linked later
// include copies the physical file
import System as sys

namespace flarp {
    // default scope is private
    class SomeThing(public sys.BaseClass(initializing_thing) ){
        // class, public, private, construct, destroy, and nothing are keywords
        public
        construct(int n)
        construct(string s)
        destroy
        nothing some_func() {
            // defined inline but it's the same as not
            // print is a library routine
            sys.print("the numeric value is {}\nthestring value is {}\n"(num, str))
        }

        private
        string str
        int num
    }

    // these do not have to be in the same file...
    SomeThing.construct(int n) {
        num = n
    }

    Something.construct(string s) {
        str = s
    }

    Something.destroy {
        // important things, in addition to the default destructor
    }

    // There is no need to define methods inside the class unless you just want to
    nothing SomeThing.some_func(int n) {
        // This override becomes a private member of the class
    }

    public nothing SomeThing.some_func(string s) {
        // This adds a public function override to the class
    }
}

// Program entry point. There must be exactly one in the root context.
// the word "start" is a keyword.
start {
    try {
        int x = sys.some_class.some_func_or_other()
        flarp.Something foob(12)
        foob.some_func()
    }
    except(SystemError as e) {
        thing.print("something bad happened with {}\n"(e))
        exit(1)
    }
    except(sys.ThingError as e) {
        thing.print("there was a system error: {}\n"(e))
    }
}

```

## This is a complete grammar for Abbr
```
#####################################################################
#
# IDENTIFIER = [_a-zA-Z][_a-zA-Z0-9]*
#
# The LITERAL_DSTR can have string escapes, similar to C++
# For formatting, look at the C++ 23+ format standard
# LITERAL_DSTR = "\"" [^\n\r]* "\""
#
# The LITERAL_SSTR is an absolute literal
# LITERAL_SSTR = "\"" [^\n\r]* "\""
#
# LITERAL_INT = ([1-9][0-9]*)|0
#
# LITERAL_UNS = 0[xX][0-9a-fA-F][0-9a-fA-F]*
#
# LITERAL_FLOAT = 0|([1-9][0-9]*)\.[0-9]+([eE][-+]?[0-9]+)?
#
# 'keywords' are -=NOT=- case-sensitive
#
#####################################################################

module
    : module_item*
    | start clause
    ;

start_clause
    : 'start' function_body
    ;

module_item
    : namespace_item
    | include_statement
    | import_statement
    ;

include_statement
    : 'include' string_literal
    ;

import_statement
    : 'import' string_literal
    | 'import' compound_name ( ('from' string_literal)? ('as' identifier)? )?
    ;

# This just makes implementing the parser easier.
identifier
    : IDENTIFIER
    ;

# note the absence of data definitions
namespace_item
    : global_scope_operator
    | class_definition
    | function_definition
    | constructor_definition
    | destructor_definition
    | namespace
    ;

# only classes can be inherited
global_scope_operator
    : 'public'
    | 'private'
    ;

class_scope_operator
    : 'public'
    | 'private'
    | 'protected'
    ;

# name spaces are concatenated, so an empty one is permissible
namespace
    : 'namespace' identifier '{' namespace_item* '}'
    ;

# at least one item must be present in a class definition.
class_definition
    : 'class' identifier ( '(' (inheritance_item (',' inheritance_item)*)? ')' )? '{' class_item+ '}'
    ;

inheritance_item
    : class_scope_operator? compound_name
    ;

class_item
    : class_scope_operator
    | function_declaration
    | data_declaration
    | constructor_declaration
    | destructor_declaration
    ;

function_declaration
    : type_specifier identifier function_declaration_parameters function_body?
    ;

constructor_declaration
    : 'create' function_declaration_parameters function_body?
    ;

destructor_declaration
    : 'destroy' function_body?
    ;

function_definition_parameters
    : '(' (data_declaration (',' data_declaration)*)? ')'
    ;

function_decl_parameter
    : type_specifier (identifier)?
    ;

function_declaration_parameters
    : '(' (function_decl_parameter (',' function_decl_parameter)*)? ')'
    ;

literal_type
    : ('integer' | 'int')
    | ('boolean' | 'bool')
    | 'string'
    | 'dict'
    | 'list'
    | 'unsigned'
    | 'float'
    | 'nothing'
    ;

type_specifier
    : literal_type
    | compound_name
    ;

function_definition
    : type_specifier identifier '.' identifier function_definition_parameters function_body
    ;

constructor_definition
    : identifier '.' 'create' function_definition_parameters function_body
    ;

destructor_definition
    : identifier '.' 'destroy' function_body
    ;

data_declaration
    : type_specifier identifier ( '=' const_value )?
    ;

compound_name
    : identifier ('.' identifier)*
    ;

literal_number
    : LITERAL_INT
    | LITERAL_UNS
    | LITERAL_FLOAT
    | LITERAL_BOOL
    ;

string_literal
    : LITERAL_SSTR
    | LITERAL_DSTR
    ;

const_value
    : literal_number
    | string_literal
    | literal_array_definition
    | literal_dict_definition
    ;

literal_string
    : LITERAL_SSTR
    | formatted_string
    ;

formatted_string
    : LITERAL_DSTR ('(' ( expression, (',' expression)* )? ')')?
    ;

literal_array_definition
    : '[' const_value (',' const_value)* ']'
    ;

literal_dict_item
    : string_literal ':' const_value
    ;

literal_dict_definition
    : '[' literal_dict_item (',' literal_dict_item)* ']'
    ;

primary_expression
    : literal_number
    | literal_string
    | compound_reference
    ;

# Expressions are parsed using the shunting yard algorithm and returned
# as an expression tree of ast_operator_t and ast_primary_expression_t.
expression
    : expression ('*' | '/' | '%') expression
    | expression '^' expression
    | expression ('+' | '-') expression
    | expression ('<' | '>' | '<=' | '>=' | 'lt' | 'gt' | 'lte' | 'gte') expression
    | expression ('==' | '!=' | 'equ' | 'neq' ) expression
    | expression ('&&' | 'and') expression
    | expression ('||' | 'or') expression
    | ('!' | 'not' | '-') expression
    | '(' expression ')'
    | primary_expression
    ;

compound_reference
    : compound_reference_item ('.' compound_reference_item)*
    ;

compound_reference_item
    : identifier
    | function_reference
    | array_reference
    ;

function_reference
    : identifier '(' expression (',' expression)* ')'
    ;

# Either arrays can hold any type as objects or only the same type as
# a normal array.
array_reference
    : identifier array_parameters (array_parameters)*
    ;

array_parameters
    : '[' (array_parameters | expression) ']'
    ;

function_body_item
    : compound_reference
    | assignment
    | data_definition
    | flow_statement
    | exit_statement
    | raise_statement
    | return_statement
    | inline_statement
    ;

# Returned as a TOK_INLINE token. The RAW_TEXT is valid C,
# including comments. Note that "{" or "}" cannot appear in
# comments because the scanner does not see them.
inline_statement
    : 'inline' '{' RAW_TEXT '}'
    ;

raise_statement
    : 'raise' '(' compound_name ')'
    ;

flow_statement
    : if_clause
    | for_clause
    | while_clause
    | do_clause
    | try_clause
    ;

loop_body_item
    : function_body_item
    | yield_statement
    | break_statement
    | continue_statement
    ;

break_statement
    : 'break'
    ;

continue_statement
    : 'continue'
    ;

yield_statement
    : 'yield' '(' expression ')'
    ;

# loop body could be empty
loop_body
    : '{' (loop_body_item | loop_body)* '}'
    ;

# function body requires at least one item
function_body
    : '{' (function_body_item | function_body)+ '}'
    ;

assignment
    : compound_reference '=' expression
    ;

data_definition
    : type_specifier identifier ( '=' expression )?
    ;

return_statement
    : 'return' ( '(' expression? ')' )?
    ;

if_clause
    : 'if' '(' expression ')' function_body ( else_clause* final_else_clause? )?
    ;

else_clause
    : 'else' '(' expression ')' function_body
    ;

# empty expressions are always taken as "true"
final_else_clause
    : 'else' ( '(' ')' )? function_body
    ;

# expressions for looping constructs are optional
for_clause
    : 'for' ( '(' ( expression ('as' (type_specifier)? identifier)? )? ')' )? loop_body
    ;

while_clause
    : 'while' ( '(' expression? ')' )? loop_body
    ;

do_clause
    : 'do' loop_body 'while' ( '(' expression? ')' )?
    ;

try_clause
    : 'try' function_body ( except_clause )+ finally_clause?
    ;

except_clause
    : 'except' '(' compound_name ('as' identifier)? ')' function_body
    ;

# executed after any exception has been handled
finally_clause
    : 'finally' function_body
    ;

exit_statement
    : 'exit' '(' expression? ')'
    ;

```
