# TODO list

* ~~Don't forget to add inline text to function items~~
* AST to dot file using the code in the expression parser template
* Decide whether arrays hold single type elements or objects.
* ~~import and include parser items~~
* implement parser modes
* ~~implement find_file() in main~~
* propagate scanner errors to the parser errors
* class must contain at least one item that is ``not a scope operator``
* symbol table and ast are dumped as a ``dot`` file from command line
* separate parser errors into expected and generic errors. 
* clean up parser error messages

# BUGS

* {} characters in inline blocks are counted no matter if they are in a comment or a string.


# NOTES

## Symbol tables

The symbol table is a tree of symbols such that symbols such as a namespace will "contain" the symbols defined under it as branches. Symbols such as local variables in a function are the leaves of the tree. Symbols are searched as locally as possible. If a symbol is not found in the current context, then it is searched in a "previous" context until the root context is encountered. For example a compound name such as "foo.bar.baz". If "foo" is not defined in the local context then the previous context is searched. If it is found, then "bar" is searched in that context. If it is found, then "baz" is searched in the context of "bar". As symbols are found, their type is checked to verify that it makes sense in the context where it is referenced. 

The symbol table is created by the parser and searched as a result of an AST pass. There is a single root symbol table that is stored in the parser context.


