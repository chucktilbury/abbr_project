project(infix_to_postfix)

include(${CMAKE_SOURCE_DIR}/CMakeBuildOpts.txt)

add_custom_target(expr)

add_executable(expr_test
    expression.c
    ast_node.c
    solver.c
    to_string.c
    tree_to_dot.c
    main.c
)

add_dependencies(expr expr_test)

target_link_libraries(expr_test
    gc
    cord
    scanner
    common
    m
)
